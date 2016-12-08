// This file was automatically generated by friendly type erasure.
// Please do not modify.

// @cond TYPE_ERASURE_DETAIL
#pragma once

#include <functional>
#include <Spacy/Util/table_util.hh>

namespace Spacy
{
    namespace CG
    {
        namespace TerminationCriterionDetail
        {
            template < class Interface >
            struct Functions
            {
                using delete_function = void ( * )( void* );
                using clone_function = void* (*)( void* );
                using call_function = bool ( * )( void* );
                using clear_function = void ( * )( void* );
                using update_double_double_double_double_function = void ( * )( void*, double alpha, double qAq,
                                                                                double qPq, double rPINVr );
                using vanishingStep_function = bool ( * )( void* );
                using minimalDecreaseAchieved_function = bool ( * )( void* );
                using setEps_double_function = void ( * )( void*, double eps );
                using setAbsoluteAccuracy_double_function = void ( * )( void*, double accuracy );
                using setMinimalAccuracy_double_function = void ( * )( void*, double accuracy );
                using setRelativeAccuracy_double_function = void ( * )( void*, double accuracy );

                delete_function del;
                clone_function clone;
                call_function call;
                clear_function clear;
                update_double_double_double_double_function update_double_double_double_double;
                vanishingStep_function vanishingStep;
                minimalDecreaseAchieved_function minimalDecreaseAchieved;
                setEps_double_function setEps_double;
                setAbsoluteAccuracy_double_function setAbsoluteAccuracy_double;
                setMinimalAccuracy_double_function setMinimalAccuracy_double;
                setRelativeAccuracy_double_function setRelativeAccuracy_double;
            };

            template < class Interface, class Impl >
            struct execution_wrapper
            {
                static bool call( void* impl )
                {
                    return static_cast< const Impl* >( impl )->operator()();
                }

                static void clear( void* impl )
                {
                    static_cast< Impl* >( impl )->clear();
                }

                static void update_double_double_double_double( void* impl, double alpha, double qAq, double qPq,
                                                                double rPINVr )
                {
                    static_cast< Impl* >( impl )->update( std::move( alpha ), std::move( qAq ), std::move( qPq ),
                                                          std::move( rPINVr ) );
                }

                static bool vanishingStep( void* impl )
                {
                    return static_cast< const Impl* >( impl )->vanishingStep();
                }

                static bool minimalDecreaseAchieved( void* impl )
                {
                    return static_cast< const Impl* >( impl )->minimalDecreaseAchieved();
                }

                static void setEps_double( void* impl, double eps )
                {
                    static_cast< Impl* >( impl )->setEps( std::move( eps ) );
                }

                static void setAbsoluteAccuracy_double( void* impl, double accuracy )
                {
                    static_cast< Impl* >( impl )->setAbsoluteAccuracy( std::move( accuracy ) );
                }

                static void setMinimalAccuracy_double( void* impl, double accuracy )
                {
                    static_cast< Impl* >( impl )->setMinimalAccuracy( std::move( accuracy ) );
                }

                static void setRelativeAccuracy_double( void* impl, double accuracy )
                {
                    static_cast< Impl* >( impl )->setRelativeAccuracy( std::move( accuracy ) );
                }
            };

            template < class Interface, class Impl >
            struct execution_wrapper< Interface, std::reference_wrapper< Impl > >
            {
                static bool call( void* impl )
                {
                    return static_cast< std::reference_wrapper< Impl >* >( impl )->get().operator()();
                }

                static void clear( void* impl )
                {
                    static_cast< std::reference_wrapper< Impl >* >( impl )->get().clear();
                }

                static void update_double_double_double_double( void* impl, double alpha, double qAq, double qPq,
                                                                double rPINVr )
                {
                    static_cast< std::reference_wrapper< Impl >* >( impl )->get().update(
                        std::move( alpha ), std::move( qAq ), std::move( qPq ), std::move( rPINVr ) );
                }

                static bool vanishingStep( void* impl )
                {
                    return static_cast< std::reference_wrapper< Impl >* >( impl )->get().vanishingStep();
                }

                static bool minimalDecreaseAchieved( void* impl )
                {
                    return static_cast< std::reference_wrapper< Impl >* >( impl )->get().minimalDecreaseAchieved();
                }

                static void setEps_double( void* impl, double eps )
                {
                    static_cast< std::reference_wrapper< Impl >* >( impl )->get().setEps( std::move( eps ) );
                }

                static void setAbsoluteAccuracy_double( void* impl, double accuracy )
                {
                    static_cast< std::reference_wrapper< Impl >* >( impl )->get().setAbsoluteAccuracy(
                        std::move( accuracy ) );
                }

                static void setMinimalAccuracy_double( void* impl, double accuracy )
                {
                    static_cast< std::reference_wrapper< Impl >* >( impl )->get().setMinimalAccuracy(
                        std::move( accuracy ) );
                }

                static void setRelativeAccuracy_double( void* impl, double accuracy )
                {
                    static_cast< std::reference_wrapper< Impl >* >( impl )->get().setRelativeAccuracy(
                        std::move( accuracy ) );
                }
            };

            template < class T >
            using TryMemFn_call = decltype( std::declval< T >().operator()() );
            template < class T, class = void >
            struct HasMemFn_call : std::false_type
            {
            };
            template < class T >
            struct HasMemFn_call< T, type_erasure_table_detail::voider< TryMemFn_call< T > > > : std::true_type
            {
            };
            template < class T >
            using TryMemFn_clear = decltype( std::declval< T >().clear() );
            template < class T, class = void >
            struct HasMemFn_clear : std::false_type
            {
            };
            template < class T >
            struct HasMemFn_clear< T, type_erasure_table_detail::voider< TryMemFn_clear< T > > > : std::true_type
            {
            };
            template < class T >
            using TryMemFn_update_double_double_double_double =
                decltype( std::declval< T >().update( std::declval< double >(), std::declval< double >(),
                                                      std::declval< double >(), std::declval< double >() ) );
            template < class T, class = void >
            struct HasMemFn_update_double_double_double_double : std::false_type
            {
            };
            template < class T >
            struct HasMemFn_update_double_double_double_double<
                T, type_erasure_table_detail::voider< TryMemFn_update_double_double_double_double< T > > >
                : std::true_type
            {
            };
            template < class T >
            using TryMemFn_vanishingStep = decltype( std::declval< T >().vanishingStep() );
            template < class T, class = void >
            struct HasMemFn_vanishingStep : std::false_type
            {
            };
            template < class T >
            struct HasMemFn_vanishingStep< T, type_erasure_table_detail::voider< TryMemFn_vanishingStep< T > > >
                : std::true_type
            {
            };
            template < class T >
            using TryMemFn_minimalDecreaseAchieved = decltype( std::declval< T >().minimalDecreaseAchieved() );
            template < class T, class = void >
            struct HasMemFn_minimalDecreaseAchieved : std::false_type
            {
            };
            template < class T >
            struct HasMemFn_minimalDecreaseAchieved<
                T, type_erasure_table_detail::voider< TryMemFn_minimalDecreaseAchieved< T > > > : std::true_type
            {
            };
            template < class T >
            using TryMemFn_setEps_double = decltype( std::declval< T >().setEps( std::declval< double >() ) );
            template < class T, class = void >
            struct HasMemFn_setEps_double : std::false_type
            {
            };
            template < class T >
            struct HasMemFn_setEps_double< T, type_erasure_table_detail::voider< TryMemFn_setEps_double< T > > >
                : std::true_type
            {
            };
            template < class T >
            using TryMemFn_setAbsoluteAccuracy_double =
                decltype( std::declval< T >().setAbsoluteAccuracy( std::declval< double >() ) );
            template < class T, class = void >
            struct HasMemFn_setAbsoluteAccuracy_double : std::false_type
            {
            };
            template < class T >
            struct HasMemFn_setAbsoluteAccuracy_double<
                T, type_erasure_table_detail::voider< TryMemFn_setAbsoluteAccuracy_double< T > > > : std::true_type
            {
            };
            template < class T >
            using TryMemFn_setMinimalAccuracy_double =
                decltype( std::declval< T >().setMinimalAccuracy( std::declval< double >() ) );
            template < class T, class = void >
            struct HasMemFn_setMinimalAccuracy_double : std::false_type
            {
            };
            template < class T >
            struct HasMemFn_setMinimalAccuracy_double<
                T, type_erasure_table_detail::voider< TryMemFn_setMinimalAccuracy_double< T > > > : std::true_type
            {
            };
            template < class T >
            using TryMemFn_setRelativeAccuracy_double =
                decltype( std::declval< T >().setRelativeAccuracy( std::declval< double >() ) );
            template < class T, class = void >
            struct HasMemFn_setRelativeAccuracy_double : std::false_type
            {
            };
            template < class T >
            struct HasMemFn_setRelativeAccuracy_double<
                T, type_erasure_table_detail::voider< TryMemFn_setRelativeAccuracy_double< T > > > : std::true_type
            {
            };

            template < class T >
            using TerminationCriterionConceptImpl = std::integral_constant<
                bool, HasMemFn_call< type_erasure_table_detail::remove_reference_wrapper_t< T > >::value &&
                          HasMemFn_clear< type_erasure_table_detail::remove_reference_wrapper_t< T > >::value &&
                          HasMemFn_update_double_double_double_double<
                              type_erasure_table_detail::remove_reference_wrapper_t< T > >::value &&
                          HasMemFn_vanishingStep< type_erasure_table_detail::remove_reference_wrapper_t< T > >::value &&
                          HasMemFn_minimalDecreaseAchieved<
                              type_erasure_table_detail::remove_reference_wrapper_t< T > >::value &&
                          HasMemFn_setEps_double< type_erasure_table_detail::remove_reference_wrapper_t< T > >::value &&
                          HasMemFn_setAbsoluteAccuracy_double<
                              type_erasure_table_detail::remove_reference_wrapper_t< T > >::value &&
                          HasMemFn_setMinimalAccuracy_double<
                              type_erasure_table_detail::remove_reference_wrapper_t< T > >::value &&
                          HasMemFn_setRelativeAccuracy_double<
                              type_erasure_table_detail::remove_reference_wrapper_t< T > >::value >;

            template < class Impl, class T, bool = std::is_same< Impl, T >::value >
            struct TerminationCriterionConcept : std::false_type
            {
            };
            template < class Impl, class T >
            struct TerminationCriterionConcept< Impl, T, false > : TerminationCriterionConceptImpl< T >
            {
            };
        }
    }
}

//@endcond
