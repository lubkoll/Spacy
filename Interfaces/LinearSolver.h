#pragma once

#include <Spacy/Vector.h>
#include <functional>

namespace Spacy
{
    /// Type-erased linear solver.
    using LinearSolver = std::function< Vector( const Vector& ) >;

    /// Type-erased indefinite linear solver. Additionally monitors if the underlying operator is
    /// positive definite.
    class IndefiniteLinearSolver
    {
    public:
        Vector operator()( const Vector& x ) const;

        bool isPositiveDefinite() const;
    };
}
