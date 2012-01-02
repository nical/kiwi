#pragma once
#ifndef KIWI_CORE_DATAPROXY_HPP
#define KIWI_CORE_DATAPROXY_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/core/Context.hpp"
#include "kiwi/core/DataHeader.hpp"

namespace kiwi{
namespace core{

class DataHeader;
class InputPort;
class OutputPort;


/**
 * @class DataProxy
 *
 * Data proxies use something some sort of reference counting in order to know how
 * many other proxies are referring to the considered one. This count is used
 * to increase the reference count of the DataHeader when calling startUsingData()
 * and the DataHeader's reference count is decremented one by one, by each node
 * that is done using the data (once the counter reaches zero the Context can
 * collect the object and place it back in the data pool or do whatever it wants
 * with it). 
 */ 
class DataProxy
{
public:
    enum{ NONE, DATA, DATATYPE, INDEX, PROXY, INPUT };

    explicit DataProxy()
    :_flag(NONE), _refCount(1)
    {
        _ptr.raw = 0;
    }
    
    explicit DataProxy( DataHeader * header )
    :_flag(DATA), _refCount(1)
    {
        _ptr.dataHeader = 0;
        setTarget( header );
    }
      
    explicit DataProxy( OutputPort * output )
    :_flag(DATATYPE), _refCount(1)
    {
        _ptr.output = 0;
        setTarget( output );
    }

    explicit DataProxy( DataProxy * proxy )
    :_flag(PROXY), _refCount(1)
    {
        _ptr.proxy = 0;
        setTarget( proxy );
    }

    explicit DataProxy( uint32 index )
    :_flag(INDEX), _refCount(1)
    {
        _ptr.index = 0;
        setTarget( index );
    }

    void setTarget( DataHeader* data );
    void setTarget( DataProxy* proxy );
    void setTarget( InputPort* input );
    void setTarget( OutputPort* output );
    void setTarget( uint32 index );
    
    DataHeader* dataHeader( Context* c ) const;
    DataHeader* dataHeader() const;

    void beginUsingData( Context* c ) const;
    void endUsingData( Context* c ) const;

    uint32 localRefCount() const
    {
        return _refCount;
    }

    uint32 totalRefCount() const
    {
        const DataProxy* it = this;
        while( it->_flag == PROXY )
            it = it->_ptr.proxy;
            
        return it->_refCount;
    }

    bool isDirectRef() const
    {
        return (_flag == INDEX) || (_flag == DATA);
    }

    uint8 proxyType() const
    {
        return _flag;
    }

    bool isAllocated() const;
    
protected:
    void increaseRefCount( uint16 nb = 1 );
    void decreaseRefCount( uint16 nb = 1 );

private:
    uint8 _flag;
    uint16 _refCount;
    union{
        void* raw;
        DataHeader* dataHeader;
        DataProxy* proxy;
        InputPort* input;
        uint32 index;
        OutputPort* output;
    } _ptr;
};


}//namepsace 
}//namepsace 

#endif
