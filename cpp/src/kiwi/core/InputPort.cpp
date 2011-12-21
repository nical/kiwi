#include "kiwi/core/InputPort.hpp"
#include "kiwi/core/OutputPort.hpp"
#include "kiwi/core/Node.hpp"
#include "kiwi/core/CompatibilityStrategy.hpp"
#include "kiwi/core/Connect.hpp"

namespace kiwi{
namespace core{

bool InputPort::connect( OutputPort& port )
{
	return kiwi::core::protocol::Connect( port, *this );
}

bool InputPort::disconnect( OutputPort& port )
{
	return kiwi::core::protocol::Disconnect( port, *this );
}

bool InputPort::disconnectAll()
{
	if( isConnected() )
		return disconnect( *connection() );
	return false;
}

bool InputPort::isCompatible(const OutputPort& port) const
{
	//if(_compatibility != 0) return true;
	//return _compatibility->isCompatible(*this, port);
    return _dataTypeInfo == port.dataType();
}

uint32 InputPort::index() const
{
    return node()->indexOf(this);
}

string InputPort::name() const
{
    return node()->type()->inputs()[index()].name();
}

Blob InputPort::data() const
{
    if (isConnected())
        return connection()->data();
    return 0;
}

}//namespace
}//namespace
