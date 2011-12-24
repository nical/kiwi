#pragma once
#ifndef KIWI_CORE_DATAPROXY_HPP
#define KIWI_CORE_DATAPROXY_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/core/Context.hpp"

namespace kiwi{
namespace core{

class DataHeader;
class InputPort;
class DataTypeInfo;

class DataProxy
{
public:
    enum{ DATA, PROXY, INPUT, NONE };

    explicit DataProxy()
    {
        _flag = NONE;
        _ptr.dataHeader = 0;
    }
    
    explicit DataProxy( DataHeader * data )
    {
        _flag = DATA;
        _ptr.dataHeader = data;
    }
    
    void setTarget( DataHeader* data );
    void setTarget( DataProxy* proxy );
    void setTarget( InputPort* input );
    void setTarget( uint32* index );

    DataHeader * data( Context * c = Context::DefaultContext() ) const;
private:
    uint8 _flag;
    union{ DataHeader* dataHeader; DataProxy* proxy; InputPort* input; } _ptr;
};



}//namepsace 
}//namepsace 

#endif
