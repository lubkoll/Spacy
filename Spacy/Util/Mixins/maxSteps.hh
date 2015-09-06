#ifndef SPACY_UTIL_MIXIN_MAXSTEPS_HH
#define SPACY_UTIL_MIXIN_MAXSTEPS_HH

#include "mixinConnection.hh"

namespace Spacy
{
  namespace Mixin
  {
    /**
     * @ingroup MixinGroup
     * @brief %Mixin class for maximal number of steps/iterations.
     */
    class MaxSteps : public MixinConnection<MaxSteps>
    {
    public:
      /**
       * @brief Constructor.
       * @param maxSteps maximal number of steps/iterations
       */
      explicit MaxSteps(unsigned maxSteps = 100) noexcept;

      /**
       * @brief Set maximal number of steps/iterations for iterative solvers.
       * @param maxSteps maximal number of steps/iterations
       */
      void setMaxSteps(unsigned maxSteps);

      /**
       * @brief Get maximal number of steps/iterations for iterative solvers.
       * @return maximal number of steps/iterations
       */
      unsigned maxSteps() const noexcept;

      /**
       * @brief Attach MaxSteps.
       *
       * When setMaxSteps(unsigned steps) is called, then also
       * other.setMaxSteps(unsigned steps) is invoked.
       */
      void attachMaxSteps(MaxSteps& other);

      /**
       * @brief Detach Eps before it gets deleted.
       */
      void detachMaxSteps(MaxSteps& other);

      /**
       * @brief update function for observer pattern.
       */
      void update(MaxSteps* changedSubject);

    private:
      unsigned maxSteps_;
    };
  }
}

#endif // SPACY_UTIL_MIXIN_MAXSTEPS_HH
