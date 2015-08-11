#ifndef ALGORITHM_ADAPTER_FENICS_OPERATOR_HH
#define ALGORITHM_ADAPTER_FENICS_OPERATOR_HH

#include <memory>
#include <vector>

#include <dolfin.h>

#include "Interface/Operator/abstractOperator.hh"
#include "Interface/Operator/linearizedOperator.hh"
#include "FunctionSpaces/ProductSpace/productSpaceElement.hh"

#include "vectorSpace.hh"
#include "../../operator.hh"
#include "Util/create.hh"
#include "Util/Mixins/disableAssembly.hh"

#include "luSolver.hh"
#include "util.hh"
#include "vector.hh"
#include "assignXIfPresent.hh"

namespace Algorithm
{
  namespace Fenics
  {
    template <class ResidualForm, class JacobianForm>
    class Operator : public Interface::AbstractOperator , public Mixin::DisableAssembly
    {
    public:
      Operator(const ResidualForm& F, const JacobianForm& J, const std::vector<const dolfin::DirichletBC*>& bcs,
                 std::shared_ptr<Interface::AbstractVectorSpace> domain,
                 std::shared_ptr<Interface::AbstractVectorSpace> range)
        : Interface::AbstractOperator( domain , range ),
          F_( F.function_space(0) ),
          J_( J.function_space(0) , J.function_space(1) ),
          bcs_( bcs ),
          dummy_( J.function_space(0) )
      {
        copyCoefficients(F,F_);
        copyCoefficients(J,J_);
      }

      Operator(const ResidualForm& F, const JacobianForm& J, const std::vector<const dolfin::DirichletBC*>& bcs,
                 std::shared_ptr<dolfin::GenericMatrix> A,
                 std::shared_ptr<Interface::AbstractVectorSpace> domain,
                 std::shared_ptr<Interface::AbstractVectorSpace> range)
        : Interface::AbstractOperator( domain , range ),
          Mixin::DisableAssembly(true),
          F_( F.function_space(0) ),
          J_( J.function_space(0) , J.function_space(1) ),
          bcs_( bcs ),
          A_(A->copy()),
          dummy_( J.function_space(0) )
      {
        copyCoefficients(F,F_);
        copyCoefficients(J,J_);
      }

      Operator(const ResidualForm& F, const JacobianForm& J, const std::vector<const dolfin::DirichletBC*>& bcs,
                 const ::Algorithm::VectorSpace& domain, const ::Algorithm::VectorSpace& range)
        : Operator(F,J,bcs,domain.sharedImpl(),range.sharedImpl())
      {}

      std::unique_ptr<Interface::AbstractVector> operator()(const Interface::AbstractVector& x) const final override
      {
        assembleOperator(x);
//        primalDualIgnoreReset(std::bind(&Operator::assembleOperator,std::ref(*this), std::placeholders::_1),x);

        auto y = range().element();
        copy(*b_,*y);
        return std::move(y);
      }

      std::unique_ptr<Interface::AbstractVector> d1(const Interface::AbstractVector &x, const Interface::AbstractVector &dx) const final override
      {
        assembleGradient(x);
//        primalDualIgnoreReset(std::bind(&Operator::assembleGradient,std::ref(*this), std::placeholders::_1),x);

        auto y_ = std::make_shared<dolfin::Vector>(dummy_.vector()->mpi_comm(), dummy_.vector()->size());
        copy(dx,*y_);
        auto Ax = y_->copy();
        A_->mult(*y_, *Ax);

        auto result = range().element();
        copy(*Ax,*result);

        return std::move(result);
      }

    private:
      friend class LinearizedOperator;

      void assembleOperator(const Interface::AbstractVector& x) const
      {
        if( assemblyIsDisabled() ) return;
        if( oldX_F != nullptr && oldX_F->equals(x) ) return;

        auto y_ = std::make_shared<dolfin::Vector>(dummy_.vector()->mpi_comm(), dummy_.vector()->size());
        copy(x,*y_);
        *dummy_.vector() = *y_;
        Assign_X_If_Present<decltype(F_)>::apply(F_,dummy_);
        b_ = dummy_.vector()->factory().create_vector();

        // Assemble right-hand side
        dolfin::Assembler assembler;
        assembler.assemble(*b_, F_);

        // Apply boundary conditions
        for(const auto& bc : bcs_)
          bc->apply( *b_ , *dummy_.vector() );

        oldX_F = clone(x);
      }

      void assembleGradient(const Interface::AbstractVector& x) const
      {
        if( assemblyIsDisabled() ) return;
        if( oldX_J != nullptr && oldX_J->equals(x) ) return;

        auto y_ = std::make_shared<dolfin::Vector>(dummy_.vector()->mpi_comm(), dummy_.vector()->size());
        copy(x,*y_);
        *dummy_.vector() = *y_;
        Assign_X_If_Present<decltype(J_)>::apply(J_,dummy_);
        A_ = dummy_.vector()->factory().create_matrix();

        // Assemble right-hand side
        dolfin::Assembler assembler;
        assembler.assemble(*A_, J_);

        // Apply boundary conditions
        for(const auto& bc : bcs_)
          bc->apply( *A_ );

        oldX_J = clone(x);
      }

      Operator* cloneImpl() const
      {
        if( assemblyIsDisabled() ) return new Operator(F_,J_,bcs_,A_,sharedDomain(),sharedRange());
        return new Operator(F_,J_,bcs_,sharedDomain(),sharedRange());
      }

      std::unique_ptr<Interface::LinearizedOperator> makeLinearization(const Interface::AbstractVector& x) const
      {
        assembleOperator(x);
        assembleGradient(x);
//        primalDualIgnoreReset(std::bind(&Operator::assembleOperator,std::ref(*this), std::placeholders::_1),x);
//        primalDualIgnoreReset(std::bind(&Operator::assembleGradient,std::ref(*this), std::placeholders::_1),x);
        return std::make_unique<Interface::LinearizedOperator>(std::make_unique<Operator>(F_,J_,bcs_,A_,sharedDomain(),sharedRange()),x);
      }

      std::unique_ptr<Interface::AbstractLinearSolver> makeSolver() const
      {
        assert (A_ != nullptr);
        return std::make_unique<LUSolver>( A_ , *F_.function_space(0) , sharedRange() , sharedDomain() );
      }

      mutable ResidualForm F_;
      mutable JacobianForm J_;
      std::vector<const dolfin::DirichletBC*> bcs_;
      mutable std::shared_ptr<dolfin::GenericMatrix> A_ = nullptr;
      mutable std::shared_ptr<dolfin::GenericVector> b_ = nullptr;
      mutable std::unique_ptr<Interface::AbstractVector> oldX_F, oldX_J = nullptr;
      mutable dolfin::Function dummy_;
    };


    /**
     * @brief Convenient generation of a differentiable operator \f$A: X\rightarrow Y\f$ as used in Fenics.
     * @return createFromUniqueImpl< ::Algorithm::Operator , ::Algorithm::Fenics::Operator<ResidualForm,JacobianForm> >( F , J , bcs , domain , range )
     */
    template <class ResidualForm, class JacobianForm>
    auto makeOperator(ResidualForm& F, JacobianForm& J, const std::vector<const dolfin::DirichletBC*>& bcs,
                        const ::Algorithm::VectorSpace& domain, const ::Algorithm::VectorSpace& range)
    {
      return createFromUniqueImpl< ::Algorithm::Operator , ::Algorithm::Fenics::Operator<ResidualForm,JacobianForm> >( F , J , bcs , domain , range );
    }

    /**
     * @brief Convenient generation of a differentiable operator \f$A: X\rightarrow X\f$ as used in Fenics.
     * @return createFromUniqueImpl< ::Algorithm::Operator , ::Algorithm::Fenics::Operator<ResidualForm,JacobianForm> >( F , J , bcs , space , space )
     */
    template <class ResidualForm, class JacobianForm>
    auto makeOperator(ResidualForm& F, JacobianForm& J, const std::vector<const dolfin::DirichletBC*>& bcs, const ::Algorithm::VectorSpace& space)
    {
      return createFromUniqueImpl< ::Algorithm::Operator , ::Algorithm::Fenics::Operator<ResidualForm,JacobianForm> >( F , J , bcs , space , space );
    }
  }
}

#endif // ALGORITHM_ADAPTER_FENICS_OPERATOR_HH
