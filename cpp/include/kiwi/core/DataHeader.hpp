#pragma once
#ifndef KIWI_CORE_DATAHEADER_HPP
#define KIWI_CORE_DATAHEADER_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/core/DataTypeId.hpp"

namespace kiwi{ 
namespace core{

class Context;

class DataHeader
{
public:
    DataTypeId type() const
    {
        return _type;
    }

    void * data() const
    {
        return _ptr;
        //return (void*)(this+1);
    }

    uint32 size() const
    {
        return _size;
    }

    uint32 totalSize() const
    {
        return sizeof(this) + size();
    }

    void incrementRefCount()
    {
        ++_refCount;
    }
    
    void decrementRefCount()
    {
        --_refCount;
        if(_refCount == 0)
            context()->markNotUsed( this );
    }
    
    uint32 refCount() const
    {
        return _refCount;
    }

    Context * context() const
    {
        return _context;
    }

    void init( Context * c, DataTypeId dataType, size_t dataSize )
    {
        _refCount = 0;
        _context = c;
        _type = dataType;
        _size = dataSize;
    }

    // temporary
    void dev_setptr( void * ptr )
    {
        _ptr = ptr;
    }

private:
    DataTypeId  _type;
    uint32      _size;
    uint32      _refCount;
    Context *   _context;
    void *      _ptr; // might be removed to have contiguously allocated data and header
};

}//namespace
}//namespace

#endif
