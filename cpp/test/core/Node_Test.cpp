
#include "kiwi/utils/Testing.hpp"
#include "kiwi/core/Node.hpp"
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

    NodeInitializer nt1init("NodeTest1");
    nt1init.addPort("in1", IN, IntInfo);
    nt1init.addPort("in1", IN, IntInfo);
    nt1init.addPort("out", OUT, IntInfo);
    nt1init.addUpdate(new mock::MockNodeUpdater);

    NodeInitializer nt2init("NodeTest2");
    nt2init.addPort("in", IN, IntInfo);
    nt2init.addPort("out", OUT, DummyInfo);
    nt2init.addUpdate(new mock::MockNodeUpdater);

    ProcessingPipeline p;

    auto n1 = new Node(&p, nt1init );
    auto n2 = new Node(&p, nt2init );

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

    delete n1;
    delete n2;
    return KIWI_END_TESTING;
}
