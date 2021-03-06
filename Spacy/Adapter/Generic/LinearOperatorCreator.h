#pragma once

#include <functional>

#include <Spacy/Util/Base/OperatorBase.h>
#include <Spacy/VectorSpace.h>

namespace Spacy
{
    namespace Generic
    {
        template < class LinearOperator >
        class LinearOperatorCreator : public OperatorBase
        {
        public:
            LinearOperatorCreator( std::function< LinearOperator( const VectorSpace* ) > creator,
                                   const VectorSpace& domain, const VectorSpace& range )
                : OperatorBase( domain, range ), creator_( std::move( creator ) )
            {
            }

            LinearOperator operator()( const VectorSpace* space ) const
            {
                return creator_( space );
            }

        private:
            std::function< LinearOperator( const VectorSpace* ) > creator_;
        };
    }
}
