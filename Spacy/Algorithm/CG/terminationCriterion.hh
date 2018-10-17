// This file was automatically generated using clang-type-erase.
// Please do not modify.

#pragma once

#include <Spacy/Util/SmartPointerStorage.h>

#include <memory>
#include <type_traits>

#include <Spacy/vector.hh>

namespace Spacy
{
    namespace CG
    {
        /// Type-erased termination criterion for conjugate gradient methods.
        class TerminationCriterion
        {
            struct Interface
            {
                virtual ~Interface() = default;
                virtual std::unique_ptr< Interface > clone() const = 0;
                virtual bool operator()() const = 0;
                virtual void clear() = 0;
                virtual void update( double alpha, double qAq, double qPq, double rPINVr,
                                     const Vector& x ) = 0;
                virtual bool vanishingStep() const = 0;
                virtual bool minimalDecreaseAchieved() const = 0;
                virtual void set_eps( double eps ) = 0;
                virtual void setAbsoluteAccuracy( double accuracy ) = 0;
                virtual void setMinimalAccuracy( double accuracy ) = 0;
                virtual void setRelativeAccuracy( double accuracy ) = 0;
            };

            template < class Impl >
            struct Wrapper : Interface
            {
                template < class T >
                Wrapper( T&& t ) : impl( std::forward< T >( t ) )
                {
                }

                std::unique_ptr< Interface > clone() const
                {
                    return std::make_unique< Wrapper< Impl > >( impl );
                }

                bool operator()() const override
                {
                    return impl.operator()();
                }

                void clear() override
                {
                    impl.clear();
                }

                void update( double alpha, double qAq, double qPq, double rPINVr,
                             const Vector& x ) override
                {
                    impl.update( std::move( alpha ), std::move( qAq ), std::move( qPq ),
                                 std::move( rPINVr ), x );
                }

                bool vanishingStep() const override
                {
                    return impl.vanishingStep();
                }

                bool minimalDecreaseAchieved() const override
                {
                    return impl.minimalDecreaseAchieved();
                }

                void set_eps( double eps ) override
                {
                    impl.set_eps( std::move( eps ) );
                }

                void setAbsoluteAccuracy( double accuracy ) override
                {
                    impl.setAbsoluteAccuracy( std::move( accuracy ) );
                }

                void setMinimalAccuracy( double accuracy ) override
                {
                    impl.setMinimalAccuracy( std::move( accuracy ) );
                }

                void setRelativeAccuracy( double accuracy ) override
                {
                    impl.setRelativeAccuracy( std::move( accuracy ) );
                }

                Impl impl;
            };

            template < class Impl >
            struct Wrapper< std::reference_wrapper< Impl > > : Wrapper< Impl& >
            {
                template < class T >
                Wrapper( T&& t ) : Wrapper< Impl& >( std::forward< T >( t ) )
                {
                }
            };

        public:
            TerminationCriterion() noexcept = default;

            template < class T,
                       typename std::enable_if< !std::is_same<
                           typename std::decay< T >::type, TerminationCriterion >::value >::type* =
                           nullptr >
            TerminationCriterion( T&& value ) : impl_( std::forward< T >( value ) )
            {
            }

            bool operator()() const
            {
                return impl_->operator()();
            }

            void clear()
            {
                impl_->clear();
            }

            void update( double alpha, double qAq, double qPq, double rPINVr, const Vector& x )
            {
                impl_->update( std::move( alpha ), std::move( qAq ), std::move( qPq ),
                               std::move( rPINVr ), x );
            }

            bool vanishingStep() const
            {
                return impl_->vanishingStep();
            }

            bool minimalDecreaseAchieved() const
            {
                return impl_->minimalDecreaseAchieved();
            }

            void set_eps( double eps )
            {
                impl_->set_eps( std::move( eps ) );
            }

            void setAbsoluteAccuracy( double accuracy )
            {
                impl_->setAbsoluteAccuracy( std::move( accuracy ) );
            }

            void setMinimalAccuracy( double accuracy )
            {
                impl_->setMinimalAccuracy( std::move( accuracy ) );
            }

            void setRelativeAccuracy( double accuracy )
            {
                impl_->setRelativeAccuracy( std::move( accuracy ) );
            }

            template < class T,
                       typename std::enable_if< !std::is_same<
                           typename std::decay< T >::type, TerminationCriterion >::value >::type* =
                           nullptr >
            TerminationCriterion& operator=( T&& value )
            {
                return *this = TerminationCriterion( std::forward< T >( value ) );
            }

            explicit operator bool() const noexcept
            {
                return bool( impl_ );
            }

            template < class T >
            T* target() noexcept
            {
                return impl_.template target< T >();
            }

            template < class T >
            const T* target() const noexcept
            {
                return impl_.template target< T >();
            }

        private:
            clang::type_erasure::polymorphic::Storage< Interface, Wrapper > impl_;
        };
    }
}
