#ifndef SPACY_UTIL_MIXIN_PRIMAL_DUAL_SWITCH_HH
#define SPACY_UTIL_MIXIN_PRIMAL_DUAL_SWITCH_HH

#include <atomic>

#include "Spacy/vector.hh"
#include "Spacy/Util/cast.hh"

namespace Spacy
{
  namespace Mixin
  {
    /**
     * @ingroup MixinGroup
     * @brief %Mixin class for separating primal and dual variables.
     */
    class PrimalDualSwitch
    {
    public:
      /// Default constructor.
      PrimalDualSwitch();

      /**
       * @brief Enable operations on primal and dual operations.
       */
      void reset() const;

      /**
       * @brief Enable operations on primal and dual operations for this object and y.
       */
      void reset(const PrimalDualSwitch& y) const;

      /**
       * @brief Disables the next operation on primal variables.
       */
      void disablePrimal() const;

      /**
       * @brief Disables the next operation on dual variables.
       */
      void disableDual() const;

      /**
       * @brief Checks if operations on primal variables are enabled.
       */
      bool isPrimalEnabled() const;

      /**
       * @brief Checks if operations on primal variables are enabled.
       */
      bool isDualEnabled() const;

      /**
       * @brief Disable reset for PrimalDualSwitch.
       */
      void disableReset() const;

      /**
       * @brief Enable reset for PrimalDualSwitch.
       */
      void enableReset() const;

    private:
      mutable std::atomic_bool disablePrimal_;
      mutable std::atomic_bool disableDual_;
      mutable std::atomic_bool disableReset_;
    };
  }

  /**
   * @brief Apply f(x) without resetting primal/dual flags in intermediate computations.
   *
   * After application of f(x), x.reset() is called. Use this if you need to maintain the restriction to
   * primal or dual variables for several operations.
   */
  template <class F>
  void primalDualIgnoreReset(F&& f, const Vector& x)
  {
    if( is<Mixin::PrimalDualSwitch>(x) ) cast_ref<Mixin::PrimalDualSwitch>(x).disableReset();
    f(x);
    if( is<Mixin::PrimalDualSwitch>(x) )
    {
      cast_ref<Mixin::PrimalDualSwitch>(x).enableReset();
      cast_ref<Mixin::PrimalDualSwitch>(x).reset();
    }
  }


  Vector& primal(Vector& x);

  const Vector& primal(const Vector& x);

  Vector& dual(Vector& x);

  const Vector& dual(const Vector& x);
}

#endif // SPACY_UTIL_MIXIN_PRIMAL_DUAL_SWITCH_HH
