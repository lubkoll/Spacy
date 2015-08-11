#ifndef ALGORITHM_REAL_NUMBERS_REAL_HH
#define ALGORITHM_REAL_NUMBERS_REAL_HH

#include <memory>

#include "Interface/abstractVector.hh"

namespace Algorithm
{
  namespace Interface { class AbstractVectorSpace; }

  /// Real number.
  class Real : public Interface::AbstractVector
  {
  public:
    /**
     * @brief Construct real number with value x.
     * @param x initial value
     * @param space associated function space (RealSpace)
     */
    Real(double x, const Interface::AbstractVectorSpace& space);

    /**
     * @brief Construct real number with initial value 0.
     * @param space associated function space (RealSpace)
     */
    explicit Real(const Interface::AbstractVectorSpace& space);

    /**
     * @brief copy data to y.
     */
    void copyTo(Interface::AbstractVector& y) const final override;

    /// Print to os.
    void print(std::ostream& os) const final override;

    /// Assignment.
    Real& operator=(const Interface::AbstractVector& y) final override;

    /// In-place summation.
    Real& operator+=(const Interface::AbstractVector& y) final override;

    /// In-place subtraction.
    Real& operator-=(const Interface::AbstractVector& y) final override;

    /// In-place multiplication.
    Real& operator*=(double) final override;

    /// Get -x.
    std::unique_ptr<Interface::AbstractVector> operator- () const final override;

    /// Access value.
    double& coefficient(unsigned) final override;

    /// Access value.
    const double& coefficient(unsigned) const final override;

    /// Number of entries in coefficient vector (=1).
    unsigned size() const final override;

    operator double() const
    {
      return x_;
    }

  private:
    /**
     * @brief Get a copy of this real number.
     */
    Real* cloneImpl() const final override;

    /// Apply as dual element.
    double applyAsDualTo(const Interface::AbstractVector& y) const final override;

    friend class RealProduct;
    double x_;
  };
}

#endif // ALGORITHM_REAL_NUMBERS_REAL_HH
