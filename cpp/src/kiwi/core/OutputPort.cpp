#include "kiwi/core/OutputPort.hpp"
#include "kiwi/core/InputPort.hpp"
#include "kiwi/core/Node.hpp"
#include "kiwi/core/Data.hpp"
#include "kiwi/core/Connect.hpp"
#include "kiwi/core/DataStrategy.hpp"

#include <assert.h>

namespace kiwi{
namespace core{


uint32 OutputPort::connect( InputPort& port )
{
	return kiwi::core::protocol::Connect(*this,port);
}

uint32 OutputPort::disconnect( InputPort& port )
{
    if( port.isConnectedTo(*this) )
        return kiwi::core::protocol::Disconnect(*this,port);
    else
        return false;
}

uint32 OutputPort::index() const
{
    return node()->indexOf(this);
}

bool OutputPort::disconnectAll()
{
    if ( !isConnected() )
        return false;
    while( _connections.size() != 0 )
    {
        disconnect(*_connections[_connections.size()-1]);
    }
    assert( !isConnected() );
	return true;
}

bool OutputPort::isCompatible(const InputPort& port) const
{
    return port.isCompatible(*this);
}

Data* OutputPort::data() const
{
    return _dataProxy.data();
}

const DataTypeInfo* OutputPort::dataType() const
{
    return _dataTypeInfo;
}

}//namespace
}//namespace
