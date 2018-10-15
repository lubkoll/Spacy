#pragma once

#include <Spacy/Spaces/ScalarSpace/Real.h>

namespace Spacy
{
    /// @cond
    class DynamicC1Operator;
    class Vector;
    /// @endcond

    namespace Rothe
    {
        Vector genericMethod( const DynamicC1Operator& A, Real t0 = 0, Real t1 = 1 );
    }
}
