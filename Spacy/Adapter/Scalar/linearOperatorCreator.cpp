#include "linearOperatorCreator.hh"

#include <stdexcept>

#include "Spacy/Spaces/realSpace.hh"
#include "Spacy/vectorSpace.hh"
#include "linearOperator.hh"

namespace Spacy
{
  namespace Scalar
  {
      LinearOperatorCreator::LinearOperatorCreator()
      {}

      LinearOperator LinearOperatorCreator::operator()(const VectorSpace* space) const
      {
        throw std::runtime_error("not implemented");
      }

      const VectorSpace& LinearOperatorCreator::domain() const
      {
        return Space::R;
      }

      const VectorSpace& LinearOperatorCreator::range() const
      {
        return Space::R;
      }
  }
}
