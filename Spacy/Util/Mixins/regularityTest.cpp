#include "regularityTest.hh"

namespace Spacy
{
  Mixin::RegularityTest::RegularityTest(Real lowerBound) noexcept
    : lowerBound_(lowerBound)
  {}

  void Mixin::RegularityTest::setLowerBound(Real lowerBound)
  {
    lowerBound_ = lowerBound;
    notify();
  }

  Real Mixin::RegularityTest::lowerBound() const noexcept
  {
    return lowerBound_;
  }

  bool Mixin::RegularityTest::regularityTestPassed(Real nu) const noexcept
  {
    return nu > lowerBound_;
  }

  bool Mixin::RegularityTest::regularityTestFailed(Real nu) const noexcept
  {
    return !regularityTestPassed(nu);
  }

  void Mixin::RegularityTest::update(MixinConnection<RegularityTest>* changedSubject)
  {
    setLowerBound( static_cast<RegularityTest*>(changedSubject)->lowerBound() );
  }

  void Mixin::RegularityTest::attachRegularityTest(RegularityTest& other)
  {
    attach(other);
  }

  void Mixin::RegularityTest::detachRegularityTest(RegularityTest& other)
  {
    detach(other);
  }
}

