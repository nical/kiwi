#pragma once
#ifndef KIWI_CORE_BLOB_HPP
#define KIWI_CORE_BLOB_HPP

#include "kiwi/core/Commons.hpp"

namespace kiwi{
namespace core{


class BlobHeader
{
friend class Blob;
public:
    uint32 type() const
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
    uint32 _type;
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

    uint32 type() const
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

    uint32 totalSize()
    {
        return _buffer->totalSize();
    }

    void * data()
    {
        return _buffer->data();
    }

    template <typename T> T* dataAs()
    {
        return (T*) data();
    }

    BlobHeader * header()
    {
        return _buffer;
    }

private:
    BlobHeader * _buffer;
};


}//namespace
}//namespace

#endif
