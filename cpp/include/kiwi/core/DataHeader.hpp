#pragma once
#ifndef KIWI_CORE_DATAHEADER_HPP
#define KIWI_CORE_DATAHEADER_HPP

#include "kiwi/core/Commons.hpp"

namespace kiwi{ 
namespace core{

class DataHeader
{
public:
    DataTypeId type() const
    {
        return _type;
    }

    void * data() const
    {
        return _data;
    }

    void incrementRefCount()
    {
        ++_refCount;
    }
    
    void decrementRefCount()
    {
        --refCount;
        if(refCount == 0)
            context()->markNotUsed( this );
    }

private:
    DataTypeId  _type;
    void *      _ptr;
    uint32      _refCount;
    Context *   _context;
};

}//namespace
}//namespace

#endif
