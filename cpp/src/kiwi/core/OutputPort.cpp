#include "kiwi/core/OutputPort.hpp"
#include "kiwi/core/InputPort.hpp"

#include "kiwi/core/Data.hpp"
#include "kiwi/core/Connect.hpp"
#include "kiwi/core/DataStrategy.hpp"

namespace kiwi{
namespace core{


bool OutputPort::connect( InputPort& port )
{
	return kiwi::core::protocol::Connect(*this,port);
}

bool OutputPort::disconnect( InputPort& port )
{
	return kiwi::core::protocol::Disconnect(*this,port);
}


bool OutputPort::disconnectAll()
{
    // TODO!
	return false;
}

bool OutputPort::isCompatible(const InputPort& port) const
{
    return port.isCompatible(*this);
}

Data* OutputPort::data() const
{
    if ( hasDataStrategy() )
        return _dataStrategy->data();
    else return 0;
}

const DataTypeInfo* OutputPort::dataType() const
{
    if ( hasDataStrategy() )
        return _dataStrategy->dataType();
    else return 0;
}

}//namespace
}//namespace
