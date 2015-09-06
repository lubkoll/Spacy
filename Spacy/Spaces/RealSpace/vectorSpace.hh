#ifndef SPACY_REAL_SPACE_CREATOR_HH
#define SPACY_REAL_SPACE_CREATOR_HH

#include "Spacy/vectorSpace.hh"

namespace Spacy
{
  namespace RealSpace
  {
    /**
     * @ingroup RealGroup
     * @brief Construct space of real numbers.
     * @return ::Spacy::makeHilbertSpace() "::Spacy::makeHilbertSpace( [](const Spacy* space){ return Vector{*space}; } , ScalarProduct{} )"
     */
    VectorSpace makeHilbertSpace();
  }

  namespace StaticDetail
  {
    static VectorSpace R = RealSpace::makeHilbertSpace();
  }
}

#endif // SPACY_REAL_SPACE_CREATOR_HH
