#pragma once

#include <Spacy/Spaces/ScalarSpace/Real.h>

namespace Spacy
{
    namespace Scalar
    {
        /// A one-dimensional quadratic function \f$q(t) = a + bt + ct^2\f$.
        class Quadratic
        {
        public:
            Quadratic( Real a, Real b, Real c ) noexcept;

            /// Compute \f$q(t) = a + bt + ct^2 \f$.
            Real operator()( Real t ) const noexcept;

        private:
            Real a_, b_, c_;
        };
    }
}
