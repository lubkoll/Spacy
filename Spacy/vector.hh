// Copyright (C) 2015 by Lars Lubkoll. All rights reserved.
// Released under the terms of the GNU General Public License version 3 or later.

#ifndef SPACY_VECTOR_HH
#define SPACY_VECTOR_HH

#include "Spacy/Util/Mixins/get.hh"
#include "Spacy/Util/Mixins/target.hh"
#include "Spacy/Util/Concepts/vectorConcept.hh"
#include "Spacy/Util/cast.hh"
#include "Spacy/Util/smartPointer.hh"
#include "Spacy/Spaces/RealSpace/real.hh"

namespace Spacy
{
  /// @cond
  class VectorSpace;
  /// @endcond

  /** @brief Type-erased vector.
   *  @see VectorConcept
   */
  class Vector : public Mixin::ToTarget<Vector>
  {
    friend class ToTarget<Vector>;

    struct AbstractBase
    {
      virtual ~AbstractBase(){}
      virtual Real operator()(const Vector& x) const = 0;
      virtual void add(const Vector& y) = 0;
      virtual void subtract(const Vector& y) = 0;
      virtual void multiply(double a) = 0;
      virtual Vector negate() const = 0;
      virtual bool compare(const Vector& y) const = 0;
      virtual const VectorSpace& space() const = 0;
      virtual void toFile(const std::string&) const = 0;
      virtual void copyFrom(const AbstractBase&) = 0;
      virtual std::unique_ptr<AbstractBase> clone() const = 0;
    };

    template <class Impl>
    struct Base : AbstractBase, Mixin::Get<Impl>
    {
      Base(Impl const& impl)
        : Mixin::Get<Impl>(impl)
      {}

      Base(Impl&& impl)
        : Mixin::Get<Impl>(std::move(impl))
      {}

      Real operator()(const Vector& x) const final override
      {
        return this->get()(*Spacy::target<Impl>(x));
      }

      void add(const Vector& y) final override
      {
        this->get() += (*Spacy::target<Impl>(y));
      }

      void subtract(const Vector& y) final override
      {
        this->get() -= (*Spacy::target<Impl>(y));
      }

      void multiply(double a) final override
      {
        this->get() *= a;
      }

      Vector negate() const final override
      {
        return Vector( -this->get() );
      }

      bool compare(const Vector& y) const final override
      {
        return this->get() == (*Spacy::target<Impl>(y));
      }

      const VectorSpace& space() const final override
      {
        return this->get().space();
      }

      void toFile(const std::string& filename) const final override
      {
        return this->get().toFile(filename);
      }

      void copyFrom(const AbstractBase& y) final override
      {
        this->get() = dynamic_cast<const Base<Impl>&>(y).get();
      }

      std::unique_ptr<AbstractBase> clone() const final override
      {
        return std::make_unique< Base<Impl> >(this->get());
      }
    };

  public:
    Vector() = default;

    /// Construct from implementation.
    template <class Impl,
              class = std::enable_if_t<!std::is_same<std::decay_t<Impl>,Vector>::value>,
              class = std::enable_if_t< VectorConcept<std::decay_t<Impl>>::value > >
    Vector(Impl&& impl)
      : base_( std::make_unique< Base< std::decay_t<Impl> > >(std::forward<Impl>(impl)) )
    {}

    /// Assign from implementation.
    template <class Impl,
              class = std::enable_if_t<!std::is_same<std::decay_t<Impl>,Vector>::value>,
              class = std::enable_if_t< VectorConcept<std::decay_t<Impl>>::value > >
    Vector& operator=(Impl&& impl)
    {
      base_ = std::make_unique< Base< std::decay_t<Impl> > >(std::forward<Impl>(impl));
      return *this;
    }


    /// Apply as dual space element.
    Real operator()(const Vector& x) const;

    Vector& operator+=(const Vector& y);

    Vector& operator-=(const Vector& y);

    Vector& operator*=(double a);

    Vector operator-() const;

    bool operator==(const Vector& y) const;

    /// Access underlying space.
    const VectorSpace& space() const;

    void toFile(const std::string& filename) const;

    /// Check if an implementation has been assigned.
    operator bool() const;

  private:
    CopyAndClonePtr<AbstractBase> base_;
  };

  /// Multiplication with arithmetic types (double,float,int,...).
  template <class Arithmetic,
            class = std::enable_if_t< std::is_arithmetic<Arithmetic>::value > >
  Vector operator*(Arithmetic a, Vector x)
  {
    return x *= a;
  }

  /// Multiplication with arithmetic types (double,float,int,...).
  template <class Arithmetic,
            class = std::enable_if_t< std::is_arithmetic<Arithmetic>::value > >
  Vector operator*(Vector x, Arithmetic a)
  {
    return x *= a;
  }

  /// Sum of vectors \f$z=x+y\f$.
  Vector operator+(Vector x, const Vector& y);

  /// Subtract vectors \f$z=x-y\f$.
  Vector operator-(Vector x, const Vector& y);

  /// Compute scalar product \f$z=x*y=(x,y)\f$.
  Real operator*(const Vector& x, const Vector& y);

  /// Compute norm, where the norm associated with the underlying function space is used \f$ z = \|x\| \f$.
  Real norm(const Vector& x);

  void checkDualPairing(const Vector& x, const Vector& y);
}

#endif // SPACY_VECTOR_HH
