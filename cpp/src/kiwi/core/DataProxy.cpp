
#include "kiwi/core/DataProxy.hpp"
#include "kiwi/core/InputPort.hpp"
#include "kiwi/core/Context.hpp"

namespace kiwi{
namespace core{

DataProxy::DataProxy( Blob * data );

Blob DataProxy::data( Context * c ) const
{
    switch( _flag )
    {
        case DATA : return *_ptr.blob;
        case DATA_IDX : return c->data( _ptr.index );
        case PROXY : return _ptr.proxy->data();
        case INPUT : return _ptr.input->data();
        default : return Blob::Null();
    }
}


}//namespace
}//namespace
