#ifndef ALGORITHM_INTERFACE_HESSIAN_HH
#define ALGORITHM_INTERFACE_HESSIAN_HH

#include <memory>

#include "abstractFunctional.hh"
#include "Interface/Operator/abstractLinearOperator.hh"
#include "Util/Mixins/impl.hh"

namespace Algorithm
{
  namespace Interface
  {
    class AbstractVector;

    class Hessian : public AbstractLinearOperator, public Mixin::UniqueImpl<AbstractFunctional>
    {
    public:
      Hessian(Hessian&&);
      Hessian(std::unique_ptr<AbstractFunctional>&& A, const AbstractVector& x);

//      Hessian(std::unique_ptr<AbstractFunctional>&& A, const AbstractVector& x, std::shared_ptr<AbstractLinearSolver> solver);

      std::unique_ptr<AbstractVector> operator ()(const AbstractVector& dx) const final override;

      std::unique_ptr<AbstractLinearSolver> solver() const final override;

    private:
      Hessian* cloneImpl() const;

      std::unique_ptr<AbstractVector> x_;
    };
  }
}

#endif // ALGORITHM_INTERFACE_HESSIAN_HH
