#include "linearizedOperator.hh"

#include "abstractC1Operator.hh"
#include "Interface/Functional/abstractC2Functional.hh"
#include "Interface/abstractFunctionSpaceElement.hh"
#include "Interface/abstractLinearSolver.hh"

#include <stdexcept>
#include <utility>

namespace Algorithm
{
  namespace Interface
  {
//    LinearizedOperator::LinearizedOperator(std::unique_ptr<AbstractC1Operator>&& A, const AbstractFunctionSpaceElement& x, std::shared_ptr<AbstractLinearSolver> solver)
//      : AbstractLinearOperator(A->getSharedDomain(),A->getSharedRange()), A_(std::move(A)), x_(clone(x)), solver_(solver)
//    {}

    LinearizedOperator::LinearizedOperator(std::unique_ptr<AbstractC1Operator>&& A, const AbstractFunctionSpaceElement& x)
      : AbstractLinearOperator(A->sharedDomain(),A->sharedRange()),
        A_(std::move(A)), x_(clone(x))
    {}


    std::unique_ptr<AbstractFunctionSpaceElement> LinearizedOperator::operator ()(const AbstractFunctionSpaceElement& dx) const
    {
      return A_->d1(*x_,dx);
    }

    std::unique_ptr<AbstractLinearSolver> LinearizedOperator::solver() const
    {
      return A_->makeSolver();
    }

    LinearizedOperator* LinearizedOperator::cloneImpl() const
    {
      return new LinearizedOperator(clone(A_),*x_/*,solver_*/);
    }
  }
}
