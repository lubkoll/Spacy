#ifndef SPACY_ADAPTER_FENICS_LUSOLVER_HH
#define SPACY_ADAPTER_FENICS_LUSOLVER_HH

#include <memory>
#include <string>

#include <dolfin.h>

#include "Spacy/vector.hh"
#include "Spacy/Util/Base/operatorBase.hh"
#include "Spacy/Util/Exceptions/callOfUndefinedFunctionException.hh"

namespace Spacy
{
  namespace FEniCS
  {
    /**
     * @ingroup FenicsGroup
     * @brief LU solver for %FEniCS.
     * @see LinearSolver
     */
    class LUSolver : public OperatorBase
    {
    public:
      /**
       * @brief Constructor.
       * @param A matrix to be inverted
       * @param space dolfin::FunctionSpace, required to initialize temporary storage
       * @param domain domain space of the solver
       * @param range range space of the solver
       * @param symmetric true if A is symmetric, else false
       * @param solverName name of the solver, i.e. "default", "mumps", "petsc" or "umfpack".
       */
      LUSolver(const dolfin::GenericMatrix& A, const dolfin::FunctionSpace& space,
               const VectorSpace& domain , const VectorSpace& range,
               bool symmetric = false, const std::string& solverName = "mumps");


      /**
       * @brief Apply LU-solver.
       * @param x right hand side for \f$A^{-1}\f$
       * @return \f$A^{-1}x\f$.
       */
      ::Spacy::Vector operator()(const ::Spacy::Vector& x) const;

    private:
      mutable dolfin::LUSolver solver_;
      const dolfin::FunctionSpace& space_;
    };

    /**
     * @ingroup FenicsGroup
     * @brief Transposed LU solver for %FEniCS.
     * @see LinearSolver
     */
    class TransposedLUSolver : public OperatorBase
    {
      /**
       * @brief Constructor.
       * @param A matrix to be transposed and inverted
       * @param space dolfin::FunctionSpace, required to initialize temporary storage
       * @param domain domain space of the solver
       * @param range range space of the solver
       * @param symmetric true if A is symmetric, else false
       * @param solverName name of the solver, i.e. "default", "mumps", "petsc" or "umfpack".
       */
    public:
      TransposedLUSolver(std::shared_ptr<dolfin::GenericMatrix> A, const dolfin::FunctionSpace& space,
                         const VectorSpace& domain , const VectorSpace& range,
               bool symmetric = false, const std::string& solverName = "mumps");

      /**
       * @brief Apply LU-solver.
       * @param x right hand side for \f$A^{-T}\f$
       * @return \f$A^{-T}x\f$.
       */
      ::Spacy::Vector operator()(const ::Spacy::Vector& x) const;

    private:
      mutable dolfin::LUSolver solver_;
      const dolfin::FunctionSpace& space_;
    };
  }
}

#endif // SPACY_ADAPTER_FENICS_LUSOLVER_HH
