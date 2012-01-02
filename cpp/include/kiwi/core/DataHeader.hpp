#pragma once
#ifndef KIWI_CORE_DATAHEADER_HPP
#define KIWI_CORE_DATAHEADER_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/core/DataTypeId.hpp"

#include <assert.h>

namespace kiwi{ 
namespace core{

class Context;
class DataRef;

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

    void increaseRefCount( uint16 nb = 1 );
    void decreaseRefCount( uint16 nb = 1 );
    
    uint16 refCount() const
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
    uint16      _refCount;
    Context *   _context;
    void *      _ptr; // might be removed to have contiguously allocated data and header
};

/*
class DataRef
{
public:
    DataRef( DataHeader * header = 0 );

    DataRef( DataHeader & header );

    DataRef( const DataRef& toCopy );

    ~DataRef();

    DataRef& operator=( DataRef& ref );
    
    DataHeader& operator*()
    {
        return *_ptr;
    }

    bool isAllocated() const
    {
        return _ptr != 0;
    }

    template<typename T> T* dataAs()
    {
        if ( _ptr ) return _ptr->dataAs<T>();
        else return 0;
    }

    void * data()
    {
        if ( _ptr ) return _ptr->data();
        else return 0;
    }

    void increaseRefcount( uint32 nb = 1 );
    void decreaseRefCount( uint32 nb = 1 );

    
    uint32 localRefCount() const
    {
        return _refCount;
    }

    uint32 totalRefCount() const
    {
        if ( _ptr ) return _ptr->refCount();
        else return _refCount;
    }
    
private:
    DataHeader * _ptr;
    uint32       _refCount;
};
*/

}//namespace
}//namespace

#endif
