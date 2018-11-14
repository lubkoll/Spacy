#pragma once

#include <deal.II/lac/sparse_direct.h>
#include <deal.II/lac/sparse_matrix.h>

#include <Spacy/Util/Base/OperatorBase.h>
#include <Spacy/Util/Cast.h>
#include <Spacy/Util/Mixins/accuracy.hh>
#include <Spacy/Util/Mixins/maxSteps.hh>
#include <Spacy/vector.hh>
#include <Spacy/vectorSpace.hh>
#include <Spacy/zeroVectorCreator.hh>

#include "util.hh"
#include "vector.hh"
#include "vectorSpace.hh"

#include <map>
#include <memory>

namespace Spacy
{
    /** @addtogroup dealIIGroup @{ */
    namespace dealII
    {
        template < class VariableDims >
        class UMFPackSolver : public OperatorBase,
                              public Mixin::AbsoluteAccuracy,
                              public Mixin::MaxSteps
        {
            using Matrix = typename Traits< VariableDims >::Matrix;

        public:
            UMFPackSolver( const Matrix& A, const Spacy::Vector& boundary_values,
                           const VectorSpace& domain, const VectorSpace& range )
                : OperatorBase( range, domain ), A_( A.get_sparsity_pattern() ),
                  solver_( std::make_shared< dealii::SparseDirectUMFPACK >() ),
                  boundary_values_( boundary_values )
            {
                A_.copy_from( A );
                solver_->initialize( A_ );
            }

            UMFPackSolver( const UMFPackSolver& other )
                : OperatorBase( other ), A_( other.A_.get_sparsity_pattern() ),
                  solver_( other.solver_ ), boundary_values_( other.boundary_values_ )
            {
                checkSpaceCompatibility( domain(), other.domain() );
                checkSpaceCompatibility( range(), other.range() );

                A_.copy_from( other.A_ );
            }

            UMFPackSolver& operator=( const UMFPackSolver& other )
            {
                checkSpaceCompatibility( domain(), other.domain() );
                checkSpaceCompatibility( range(), other.range() );

                A_.copy_from( other.A_ );
                solver_ = other.solver_;
                boundary_values_ = other.boundary_values_;
                return *this;
            }

            ::Spacy::Vector operator()( Spacy::Vector x ) const
            {
                auto& x_ = cast_ref< Vector >( x );

                auto y = zero( range() );
                auto& y_ = cast_ref< Vector >( y );

                solver_->vmult( get( y_ ), get( x_ ) );

                return y + boundary_values_;
            }

        private:
            mutable Matrix A_;
            std::shared_ptr< dealii::SparseDirectUMFPACK > solver_;
            Spacy::Vector boundary_values_;
        };
    }
    /** @} */
}
