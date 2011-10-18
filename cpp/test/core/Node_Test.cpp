
#include "kiwi/utils/Testing.hpp"
#include "kiwi/core/Node.hpp"
#include "kiwi/core/NodeTypeManager.hpp"
#include "kiwi/core/InputPort.hpp"
#include "kiwi/core/OutputPort.hpp"
#include "kiwi/core/OpConnect.hpp"
#include "kiwi/core/Container.hpp"
#include "kiwi/extern/log/DebugStream.hpp"
#include "kiwi/processing/ProcessingPipeline.hpp"
#include "kiwi/mock/MockNodeUpdater.hpp"

using namespace kiwi;
using namespace kiwi::core;
using namespace kiwi::processing;

struct Dummy{};
KIWI_DECLARE_CONTAINER(int,"Int");
KIWI_DECLARE_CONTAINER(Dummy,"Dummy");


int main()
{
	KIWI_BEGIN_TESTING("Kiwi::core::Node");

    auto IntInfo = RegisterDataType("Int", &Newint);
    auto DummyInfo = RegisterDataType("Dummmy", &NewDummy);

    

    NodeLayoutDescriptor layout1;
    layout1.inputs =
    {
        InputPortDescriptor("in1", IntInfo, READ),
        InputPortDescriptor("in2", IntInfo, READ)
    };
    layout1.outputs =
    {
        OutputPortDescriptor("out", IntInfo, READ )
    };

    assert( layout1.inputs[1].dataType() == IntInfo );
    
    //nt1init.addUpdate(new mock::MockNodeUpdater);

    NodeLayoutDescriptor layout2;
    layout2.inputs =
    {
        InputPortDescriptor("in", IntInfo, READ)
    };
    layout2.outputs =
    {
        OutputPortDescriptor("out", DummyInfo, READ )
    };
    
    //nt2init.addUpdate(new mock::MockNodeUpdater);

    NodeTypeManager::RegisterNode("NodeTest1", layout1, new mock::MockNodeUpdater);
    NodeTypeManager::RegisterNode("NodeTest2", layout2, new mock::MockNodeUpdater);
    
    ProcessingPipeline p;

    auto n1 = new Node(&p, NodeTypeManager::TypeOf("NodeTest1") );
    auto n2 = new Node(&p, NodeTypeManager::TypeOf("NodeTest2") );

    {   SCOPEDBLOCK("Initial state");
        KIWI_TEST("Number of input ports.", n1->inputs().size() == 2 );
        KIWI_TEST("Number of output ports.", n1->outputs().size() == 1 );
        KIWI_TEST("Input 1 data type.", n1->inputs()[0]->dataType() == IntInfo );
        KIWI_TEST("Input 2 data type.", n1->inputs()[1]->dataType() == IntInfo );
        KIWI_TEST("Output 1 data type.", n1->outputs()[0]->dataType() == IntInfo );

        KIWI_TEST("Input is not connected.", ! n2->input().isConnected() );
        KIWI_TEST("Input is not connected to.", ! n2->input().isConnectedTo( n1->output() ) );
        KIWI_TEST("Output is not connected.", ! n1->output().isConnected() );
        KIWI_TEST("Output is not connected to.", ! n1->output().isConnectedTo( n2->input() ) );
    }
    
    {   SCOPEDBLOCK("Compatibility");
        KIWI_TEST("Compatibility", n1->output().isCompatible( n2->input() ) ); // int - int
        KIWI_TEST("Incompatibility", ! n2->output().isCompatible( n1->input() ) ); // dummy - int
    }
    
    {   SCOPEDBLOCK("Connection/disconnection");

        KIWI_TEST("Connection", n1->output() >> n2->input() );

        KIWI_TEST("Input is connected.", n2->input().isConnected() );
        KIWI_TEST("Input is connected to.", n2->input().isConnectedTo( n1->output() ) );
        KIWI_TEST("Output is connected.", n1->output().isConnected() );
        KIWI_TEST("Output is connected to.", n1->output().isConnectedTo( n2->input() ) );

        KIWI_TEST("Disconnection", n1->output().disconnect( n2->input() ) );

        KIWI_TEST("Input is not connected.", ! n2->input().isConnected() );
        KIWI_TEST("Input is not connected to.", ! n2->input().isConnectedTo( n1->output() ) );
        KIWI_TEST("Output is not connected.", ! n1->output().isConnected() );
        KIWI_TEST("Output is not connected to.", ! n1->output().isConnectedTo( n2->input() ) );

        KIWI_TEST("Reconnection", n1->output() >> n2->input() );

        KIWI_TEST("Input is connected.", n2->input().isConnected() );
        KIWI_TEST("Input is connected to.", n2->input().isConnectedTo( n1->output() ) );
        KIWI_TEST("Output is connected.", n1->output().isConnected() );
        KIWI_TEST("Output is connected to.", n1->output().isConnectedTo( n2->input() ) );

        KIWI_TEST("Disconnect all", n1->output().disconnectAll() );

        KIWI_TEST("Input is not connected.", ! n2->input().isConnected() );
        KIWI_TEST("Input is not connected to.", ! n2->input().isConnectedTo( n1->output() ) );
        KIWI_TEST("Output is not connected.", ! n1->output().isConnected() );
        KIWI_TEST("Output is not connected to.", ! n1->output().isConnectedTo( n2->input() ) );

        KIWI_TEST("Incompatible connetion.", ! (n2->output() >> n1->input()) );
        
        KIWI_TEST("Input is not connected.", ! n2->output().isConnected() );
        KIWI_TEST("Input is not connected to.", ! n2->output().isConnectedTo( n1->input() ) );
        KIWI_TEST("Output is not connected.", ! n1->input().isConnected() );
        KIWI_TEST("Output is not connected to.", ! n1->input().isConnectedTo( n2->output() ) );
    }
    
    {   SCOPEDBLOCK("Update");
        mock::MockNodeUpdater::updateCount = 0;
        n1->update();
        n2->update();
        KIWI_TEST_EQUAL("Number of updates.", mock::MockNodeUpdater::updateCount, 2  );
    }

    delete n1;
    delete n2;
    return KIWI_END_TESTING;
}
