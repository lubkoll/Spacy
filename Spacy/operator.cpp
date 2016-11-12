// This file was automatically generated by friendly type erasure.
// Please do not modify.

#include "operator.hh"

namespace Spacy
{
    Operator::Operator() noexcept : impl_( nullptr )
    {
    }

    Operator::Operator( const Operator& other )
        : functions_( other.functions_ ), type_id_( other.type_id_ ), impl_( other.impl_ )
    {
        if ( !type_erasure_table_detail::is_heap_allocated( other.impl_.get(), other.buffer_ ) )
            other.functions_.clone_into( other.impl_.get(), buffer_, impl_ );
    }

    Operator::Operator( Operator&& other ) noexcept : functions_( other.functions_ ), type_id_( other.type_id_ )
    {
        if ( type_erasure_table_detail::is_heap_allocated( other.impl_.get(), other.buffer_ ) )
            impl_ = std::move( other.impl_ );
        else
            other.functions_.clone_into( other.impl_.get(), buffer_, impl_ );
        other.impl_ = nullptr;
    }

    Operator& Operator::operator=( const Operator& other )
    {
        functions_ = other.functions_;
        type_id_ = other.type_id_;
        impl_ = other.impl_;
        if ( !type_erasure_table_detail::is_heap_allocated( other.impl_.get(), other.buffer_ ) )
            other.functions_.clone_into( other.impl_.get(), buffer_, impl_ );
        return *this;
    }

    Operator& Operator::operator=( Operator&& other ) noexcept
    {
        type_id_ = other.type_id_;
        functions_ = other.functions_;
        if ( type_erasure_table_detail::is_heap_allocated( other.impl_.get(), other.buffer_ ) )
            impl_ = std::move( other.impl_ );
        else
            other.functions_.clone_into( other.impl_.get(), buffer_, impl_ );
        other.impl_ = nullptr;
        return *this;
    }

    Operator::operator bool() const noexcept
    {
        return impl_ != nullptr;
    }

    Vector Operator::operator()( const Vector& x ) const
    {
        assert( impl_ );
        return functions_.call_const_Vector_ref( *this, read(), x );
    }

    const VectorSpace& Operator::domain() const
    {
        assert( impl_ );
        return functions_.domain( *this, read() );
    }

    const VectorSpace& Operator::range() const
    {
        assert( impl_ );
        return functions_.range( *this, read() );
    }

    void* Operator::read() const noexcept
    {
        assert( impl_ );
        return impl_.get();
    }

    void* Operator::write()
    {
        assert( impl_ );
        if ( !impl_.unique() && type_erasure_table_detail::is_heap_allocated( impl_.get(), buffer_ ) )
            functions_.clone( read(), impl_ );
        return read();
    }
}
