#include "kiwi/core/Connect.hpp"
#include "kiwi/core/InputPort.hpp"
#include "kiwi/core/OutputPort.hpp"


namespace kiwi{
namespace core{
namespace protocol{

bool Connect( OutputPort& output, InputPort& input )
{
	if ( !input.isCompatible( output ) )
		return false;

	if ( input.isConnected() ) input.disconnectAll();

	input._connection = &output;
	output._connections.push_back( &input );

	return true;
}

bool Disconnect( OutputPort& output, InputPort& input )
{

	if ( !input.isConnected() ) return false;

	int i2 = output._indexOf(input);

	// proceed with the disconnection
	input._connection = 0;
	output._connections[i2] = output._connections[output._connections.size() -1];
	output._connections.resize( output._connections.size() -1 );
	return true;

}

}//namespace
}//namespace
}//namespace
