#include "kiwi/core/OutputPort.hpp"

namespace kiwi{
namespace core{


bool OutputPort::connect( InputPort& port )
{
	return false;
}

bool OutputPort::disconnect( InputPort& port )
{
	return false;
}


bool OutputPort::disconnectAll()
{
	return false;
}

}//namespace
}//namespace
