#pragma once
#ifndef KIWI_CORE_DATAPROXY_HPP
#define KIWI_CORE_DATAPROXY_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/core/Context.hpp"

namespace kiwi{
namespace core{

class Blob;
class InputPort;
class DataTypeInfo;

class DataProxy
{
public:
    enum{ DATA, PROXY, INPUT, DATA_IDX, NONE };

    explicit DataProxy()
    {
        _flag = NONE;
        _ptr.blob = 0;
    }
    
    explicit DataProxy( Blob * data )
    {
        _flag = DATA;
        _ptr.blob = data;
    }
    
    void setTarget( Blob* data );
    void setTarget( DataProxy* proxy );
    void setTarget( InputPort* input );
    void setTarget( uint32* index );

    Blob data( Context * c = Context::Default() ) const;
private:
    uint8 _flag;
    union{ Blob* blob; DataProxy* proxy; InputPort* input; uint32 index; } _ptr;
};



}//namepsace 
}//namepsace 

#endif
