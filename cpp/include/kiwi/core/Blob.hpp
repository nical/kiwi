#pragma once
#ifndef KIWI_CORE_BLOB_HPP
#define KIWI_CORE_BLOB_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/core/TypeIndex.hpp"


/**
 * Creates the function that instanciates the container (needed to register the data type).
 */ 
#define KIWI_DECLARE_CONTAINER_AND_NAME( type ) kiwi::core::Blob New##type(){ kiwi::core::Blob b; b.AllocateFromType<type>(); return b; }
/**
 * Creates the function that instanciates the container (needed to register the data type).
 */ 
#define KIWI_DECLARE_CONTAINER( type, name ) kiwi::core::Blob New##type(){ kiwi::core::Blob b; b.AllocateFromType<type>(); return b; } 



namespace kiwi{
namespace core{


class BlobHeader
{
friend class Blob;
public:
    size_t type() const
    {
        return _type;
    }
    uint32 flags() const
    {
        return _flags;
    }
    uint32 size() const
    {
        return _size;
    }

    uint32 totalSize()
    {
        return sizeof(this) + size();
    }

    void * data()
    {
        return (void*) (this+1);
    }
private:
    size_t _type;
    uint32 _flags;
    uint32 _size;
    uint32 _padding;
};

class Blob
{
public:
    Blob( uint32 bufferSize = 0, uint32 btype = 0, uint32 bflags = 0 );
    ~Blob();
    
    void allocate( uint32 bufferSize, uint32 btype = 0, uint32 bflags = 0 );
    void deallocate();

    bool isAllocated() const
    {
        return _buffer != 0;
    }

    size_t type() const
    {
        return _buffer->type();
    }
    uint32 flags() const
    {
        return _buffer->flags();
    }
    uint32 size() const
    {
        return _buffer->size();
    }

    uint32 totalSize() const
    {
        return _buffer->totalSize();
    }

    void * data() const
    {
        return _buffer->data();
    }

    template <typename T> T* dataAs() const
    {
        return (T*) data();
    }

    BlobHeader * header() const
    {
        return _buffer;
    }
    
    bool operator == ( Blob b )
    {
        return _buffer == b._buffer;
    }

    bool operator != ( Blob b )
    {
        return _buffer != b._buffer;
    }

    static Blob Null()
    {
        return Blob();
    }

    template<typename T> void AllocateFromType()
    {
        deallocate();
        allocate( sizeof(T), TypeIndexOf<T>() );
        new ( data() ) T; // placement new
    }

private:
    BlobHeader * _buffer;
};

}//namespace
}//namespace

#endif
