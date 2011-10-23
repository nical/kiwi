#include "kiwi/core/Connect.hpp"
#include "kiwi/core/InputPort.hpp"
#include "kiwi/core/OutputPort.hpp"
#include "kiwi/core/Node.hpp"
#include <assert.h>


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

    if ( output.node() )
        output.node()->outputConnected(&output,&input);
    if ( input.node() )
        input.node()->inputConnected(&input,&output);

	return true;
}

bool Disconnect( OutputPort& output, InputPort& input )
{
    SCOPEDBLOCK("protocol::Disconnect");

    if ( !input.isConnectedTo(output) ) return false;

	int i2 = output._indexOf(input);

    if ( i2 > 0 ){
        assert( output._connections[i2]->node() == input.node() );
    }
	// proceed with the disconnection
	input._connection = 0;
	output._connections[i2] = output._connections[output._connections.size() -1];
	output._connections.resize( output._connections.size() -1 );

    if ( output.node() )
        output.node()->outputDisconnected(&output,&input);
    if ( input.node() )
        input.node()->inputDisconnected(&input,&output);
    
	return true;

}

}//namespace
}//namespace
}//namespace
