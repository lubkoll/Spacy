#include "LinearOperator.h"

#include <Spacy/Vector.h>
#include <Spacy/ZeroVectorCreator.h>

#include "Copy.h"
#include "LinearSolver.h"
#include "Vector.h"

namespace Spacy
{
    namespace Rn
    {
        LinearOperator::LinearOperator(::Eigen::MatrixXd A, const VectorSpace& space,
                                       const VectorSpace& domain, const VectorSpace& range )
            : Mixin::Get<::Eigen::MatrixXd >( std::move( A ) ), VectorBase( space ),
              OperatorBase( domain, range )
        {
        }

        ::Spacy::Vector LinearOperator::operator()( const ::Spacy::Vector& dx ) const
        {
            ::Eigen::VectorXd dx_;
            copy( dx, dx_ );
            ::Eigen::VectorXd x_ = get() * dx_;
            auto x = zero( dx.space() );
            copy( x_, x );
            return x;
        }

        Real LinearOperator::operator()( const LinearOperator& ) const
        {
            return Real( 0 );
        }

        LinearSolver LinearOperator::solver() const
        {
            return LinearSolver( get(), domain() );
        }
    }
}
