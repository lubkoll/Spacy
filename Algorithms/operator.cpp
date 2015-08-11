#include "operator.hh"

#include "vector.hh"
#include "linearOperator.hh"

#include "Interface/Operator/linearizedOperator.hh"
#include "Util/castTo.hh"


#include <utility>

namespace Algorithm
{
  Operator::Operator(std::unique_ptr<Interface::AbstractOperator>&& implementation)
    : Mixin::UniqueImpl<Interface::AbstractOperator>(std::move(implementation)),
      domain_( impl().sharedDomain() ),
      range_( impl().sharedRange() )
  {}

  Vector Operator::operator()(const Vector& x) const
  {
    return impl()(x.impl());
  }

  Vector Operator::d1(const Vector& x, const Vector& dx) const
  {
    return impl().d1( x.impl() , dx.impl() );
  }

  Vector Operator::d2(const Vector& x, const Vector& dx, const Vector& dy) const
  {
    return impl().d2(x.impl(),dx.impl(),dy.impl());
  }

  LinearOperator Operator::linearization(const Vector& x) const
  {
    return LinearOperator( impl().linearization(x.impl()) );
  }

  VectorSpace& Operator::domain()
  {
    return domain_;
  }

  const VectorSpace& Operator::domain() const
  {
    return domain_;
  }

  VectorSpace& Operator::range()
  {
    return range_;
  }

  const VectorSpace& Operator::range() const
  {
    return range_;
  }
}
