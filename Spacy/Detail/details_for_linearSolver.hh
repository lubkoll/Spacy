// This file was automatically generated by friendly type erasure.
// Please do not modify.

// @cond#pragma once

#include <functional>
#include <Spacy/Util/table_util.hh>
#include <Spacy/vector.hh>

namespace Spacy
{
    namespace IndefiniteLinearSolverDetail
    {
        template < class Interface >
        struct Functions
        {
            using delete_function = void ( * )( void* );
            using clone_function = void* (*)( void* );
            using call_const_Vector_ref_function = Vector ( * )( const Interface&, void*, const Vector& x );
            using isPositiveDefinite_function = bool ( * )( const Interface&, void* );

            delete_function del;
            clone_function clone;
            call_const_Vector_ref_function call_const_Vector_ref;
            isPositiveDefinite_function isPositiveDefinite;
        };

        template < class Interface, class Impl >
        struct execution_wrapper
        {
            static Vector call_const_Vector_ref( const Interface& interface, void* impl, const Vector& x )
            {
                return static_cast< const Impl* >( impl )->operator()( x );
            }

            static bool isPositiveDefinite( const Interface& interface, void* impl )
            {
                return static_cast< const Impl* >( impl )->isPositiveDefinite();
            }
        };

        template < class Interface, class Impl >
        struct execution_wrapper< Interface, std::reference_wrapper< Impl > >
        {
            static Vector call_const_Vector_ref( const Interface& interface, void* impl, const Vector& x )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().operator()( x );
            }

            static bool isPositiveDefinite( const Interface& interface, void* impl )
            {
                return static_cast< std::reference_wrapper< Impl >* >( impl )->get().isPositiveDefinite();
            }
        };

        template < class T >
        using TryMemFn_call_const_Vector_ref = decltype( std::declval< T >().operator()( std::declval< Vector >() ) );
        template < class T, class = void >
        struct HasMemFn_call_const_Vector_ref : std::false_type
        {
        };
        template < class T >
        struct HasMemFn_call_const_Vector_ref<
            T, type_erasure_table_detail::voider< TryMemFn_call_const_Vector_ref< T > > > : std::true_type
        {
        };
        template < class T >
        using TryMemFn_isPositiveDefinite = decltype( std::declval< T >().isPositiveDefinite() );
        template < class T, class = void >
        struct HasMemFn_isPositiveDefinite : std::false_type
        {
        };
        template < class T >
        struct HasMemFn_isPositiveDefinite< T, type_erasure_table_detail::voider< TryMemFn_isPositiveDefinite< T > > >
            : std::true_type
        {
        };

        template < class T >
        using IndefiniteLinearSolverConceptImpl = std::integral_constant<
            bool,
            HasMemFn_call_const_Vector_ref< type_erasure_table_detail::remove_reference_wrapper_t< T > >::value &&
                HasMemFn_isPositiveDefinite< type_erasure_table_detail::remove_reference_wrapper_t< T > >::value >;

        template < class Impl, class T, bool = std::is_same< Impl, T >::value >
        struct IndefiniteLinearSolverConcept : std::false_type
        {
        };
        template < class Impl, class T >
        struct IndefiniteLinearSolverConcept< Impl, T, false > : IndefiniteLinearSolverConceptImpl< T >
        {
        };
    }
}

//@endcond
