#pragma once

#include <functional>

#include <Spacy/Spaces/ProductSpace/vector.hh>
#include <Spacy/Util/Cast.h>
#include <Spacy/vector.hh>

namespace Spacy
{
    /// @cond
    template < class Target >
    void copyProductSpaceVectorIfConsistent(
        const Vector& x, Target& y,
        std::function< void( const Vector&, Target& ) > copyTargetIfConsistent )
    {
        if ( !is< ProductSpace::Vector >( x ) )
            return;

        const auto& x_ = cast_ref< ProductSpace::Vector >( x );

        for ( auto i = 0u; i < x_.numberOfVariables(); ++i )
        {
            copyTargetIfConsistent( x_.component( i ), y );
            copyProductSpaceVectorIfConsistent( x_.component( i ), y, copyTargetIfConsistent );
        }
    }

    template < class Target >
    void copyProductSpaceVectorIfConsistent(
        const Target& x, Vector& y,
        std::function< void( const Target&, Vector& ) > copyTargetIfConsistent )
    {
        if ( !is< ProductSpace::Vector >( y ) )
            return;

        auto& y_ = cast_ref< ProductSpace::Vector >( y );

        for ( auto i = 0u; i < y_.numberOfVariables(); ++i )
        {
            copyTargetIfConsistent( x, y_.component( i ) );
            copyProductSpaceVectorIfConsistent( x, y_.component( i ), copyTargetIfConsistent );
        }
    }
    /// @endcond

    /**
     * @brief Copy from x to y.
     *
     * One of Origin or Target is a Spacy::Vector, the other is some other type.
     * This function treats (nested) product space structures and uses copyTargetIfConsistent to
     * copy single subspaces.
     */
    template < class Origin, class Target >
    void genericCopy( const Origin& x, Target& y,
                      std::function< void( const Origin&, Target& ) > copyTargetIfConsistent )
    {
        copyTargetIfConsistent( x, y );
        copyProductSpaceVectorIfConsistent( x, y, copyTargetIfConsistent );
    }
}
