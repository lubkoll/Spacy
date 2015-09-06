#include "terminationCriteria.hh"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <limits>

#include <iostream>

namespace Spacy
{
  namespace CG
  {
    namespace Termination
    {
      bool StrakosTichyEnergyError::operator()() const
      {
        auto tol = max( relativeAccuracy() , eps() );
        if( verbosityLevel() > 1 ) std::cout << "      termination criterion (relative error): " << sqrt(squaredRelativeError()) << "\n      tolerance: " << tol << std::endl;
        return scaledGamma2.size() > maxSteps() || ( scaledGamma2.size() > lookAhead_ && squaredRelativeError() < tol*tol );
      }


      void StrakosTichyEnergyError::update(Real alpha, Real qAq, Real, Real rPINVr)
      {
        scaledGamma2.push_back( alpha * rPINVr );
        energyNorm2 += alpha * rPINVr;
        stepLength2 = abs(qAq);
      }

      bool StrakosTichyEnergyError::vanishingStep() const noexcept
      {
        Real tol = absoluteAccuracy()*absoluteAccuracy();
        if( energyNorm2 > tol) tol = min(tol,eps()*eps()*energyNorm2);
        return stepLength2 < tol;
      }

      void StrakosTichyEnergyError::clear() noexcept
      {
        scaledGamma2.clear();
        energyNorm2 = 0;
      }

      void StrakosTichyEnergyError::setLookAhead(unsigned lookAhead) noexcept
      {
        lookAhead_ = lookAhead;
      }

      bool StrakosTichyEnergyError::minimalDecreaseAchieved() const noexcept
      {
        return squaredRelativeError() < minimalAccuracy()*minimalAccuracy();
      }

      Real StrakosTichyEnergyError::squaredRelativeError() const noexcept
      {
        if( scaledGamma2.size() < lookAhead_ ) return std::numeric_limits<double>::max();
        return std::accumulate(scaledGamma2.end() - lookAhead_, scaledGamma2.end(), Real{0.}) / energyNorm2;
      }
    }
  }
}
