#pragma once

#include <Spacy/Spaces/ScalarSpace/Real.h>
#include <Spacy/vector.hh>
#include <Spacy/vectorSpace.hh>

namespace Spacy
{
    /// Type-erased functional \f$f:\ X \to \mathbb{R} \f$.
    class Functional
    {
    public:
        /// Apply functional.
        Real operator()( const Vector& x ) const;

        /// Access domain space \f$X\f$.
        const VectorSpace& domain() const;
    };
}
