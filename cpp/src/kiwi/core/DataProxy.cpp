
#include "kiwi/core/DataProxy.hpp"
#include "kiwi/core/InputPort.hpp"
#include "kiwi/core/Context.hpp"
#include "kiwi/core/DataHeader.hpp"

namespace kiwi{
namespace core{


DataHeader * DataProxy::data( Context * c ) const
{
    switch( _flag )
    {
/*        case DATA : return _ptr.dataHeader;
        //case DATA_IDX : return c->requestData( _ptr.index );
        case PROXY : return _ptr.proxy->data();
        case INPUT : return _ptr.input->data();
*/        default : return 0;
    }
}


}//namespace
}//namespace
