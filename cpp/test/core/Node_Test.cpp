
#include "kiwi/utils/Testing.hpp"
#include "kiwi/core/Node.hpp"
#include "kiwi/core/DataTypeManager.hpp"
#include "kiwi/core/NodeTypeManager.hpp"
#include "kiwi/core/InputPort.hpp"
#include "kiwi/core/OutputPort.hpp"
#include "kiwi/core/OpConnect.hpp"
#include "kiwi/core/Container.hpp"
#include "kiwi/extern/log/DebugStream.hpp"
#include "kiwi/mock/MockNodeUpdater.hpp"
#include "kiwi/mock/MockPipeline.hpp"


using namespace kiwi;
using namespace kiwi::core;

struct Dummy{};
KIWI_DECLARE_CONTAINER(int,"Int")
KIWI_DECLARE_CONTAINER(Dummy,"Dummy")


#define PRINT_NODES( n, prevOrNext )  \
log << #prevOrNext << ":" << endl; \
for( auto it = n->prevOrNext().begin(); it != n->prevOrNext().end(); ++it ) \
{ if( *it == 0 ) log << ": null"  << endl; \
else log << ": " << (*it)->id() << endl; }

#define PRINT_OUT_CONNECTIONS( n )  \
log << "| outputs:" << endl; \
for( auto itp = n->outputs().begin(); itp != n->outputs().end(); ++itp ) \
for( auto itc = (*itp)->connections().begin(); itc != (*itp)->connections().end(); ++itc ) \
{ log << "| " << (*itc)->node()->id() << endl; }



void printNodeLayout( Node* n )
{
        log << "Node id=" << n->id() << endl;
        log << "inputs: {";
        for( auto itp = n->inputs().begin(); itp != n->inputs().end(); ++itp )
        {
            if ( (*itp)->isConnected() )
                log << (*itp)->connection()->node()->id() << " ";
            else
                log << "# ";
        }
        log << "} " << endl << "outputs: {";
        for( auto itp = n->outputs().begin(); itp != n->outputs().end(); ++itp )
        {
            for( auto itc = (*itp)->connections().begin(); itc != (*itp)->connections().end(); ++itc )
            {
                log << (*itc)->node()->id() << " ";
            }
        }
        log << "} " << endl;
}


int main()
{
	KIWI_BEGIN_TESTING("Kiwi::core::Node");

    auto IntInfo = DataTypeManager::RegisterDataType("Int", &Newint);
    auto DummyInfo = DataTypeManager::RegisterDataType("Dummy", &NewDummy);

    

    NodeLayoutDescriptor layout1;
    layout1.inputs =
    {
        { "in1", IntInfo, READ },
        { "in2", IntInfo, READ }
    };
    layout1.outputs =
    {
        { "out", IntInfo, READ }
    };

    assert( layout1.inputs[1].dataType() == IntInfo );
    
    NodeLayoutDescriptor layout2;
    layout2.inputs =
    {
        { "in", IntInfo, READ }
    };
    layout2.outputs =
    {
        { "out", DummyInfo, READ }
    };

    NodeLayoutDescriptor layout3;
    layout3.inputs =
    {
        { "in1", IntInfo, READ },
        { "in2", IntInfo, READ },
        { "in3", IntInfo, READ }
    };
    layout3.outputs =
    {
        { "out1", IntInfo, READ },
        { "out2", IntInfo, READ },
        { "out3", IntInfo, READ }
    };

    NodeTypeManager::RegisterNode("NodeTest1", layout1, new mock::MockNodeUpdater);
    NodeTypeManager::RegisterNode("NodeTest2", layout2, new mock::MockNodeUpdater);
    NodeTypeManager::RegisterNode("NodeTest3", layout3, new mock::MockNodeUpdater);
    
    Pipeline* p = mock::NewMockPipeline();

    auto n1 = NodeTypeManager::TypeOf("NodeTest1")->newInstance(p);
    auto n2 = NodeTypeManager::TypeOf("NodeTest2")->newInstance(p);

    {   SCOPEDBLOCK("Initial state");
        KIWI_TEST("Number of input ports.", n1->inputs().size() == 2 );
        KIWI_TEST("Number of output ports.", n1->outputs().size() == 1 );
        KIWI_TEST("Input 1 data type.", n1->inputs()[0]->dataType() == IntInfo );
        KIWI_TEST("Input 2 data type.", n1->inputs()[1]->dataType() == IntInfo );
        KIWI_TEST("Output 1 data type.", n1->outputs()[0]->dataType() == IntInfo );
        KIWI_TEST("Access input by name", &n1->input("in1") == &n1->input(0) );
        KIWI_TEST("Access input by name", &n1->input("in2") == &n1->input(1) );
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

    {   SCOPEDBLOCK("Previous/next nodes");
        KIWI_TEST_EQUAL("Number of previous nodes.", n1->previousNodes().size(), 0); 
        KIWI_TEST_EQUAL("Number of next nodes.", n1->nextNodes().size(), 0);
        n1->output() >> n2->input();
        KIWI_TEST_EQUAL("Number of previous nodes.", n1->previousNodes().size(), 0); 
        KIWI_TEST_EQUAL("Number of next nodes.", n1->nextNodes().size(), 1);
        KIWI_TEST_EQUAL("Number of previous nodes.", n2->previousNodes().size(), 1); 
        KIWI_TEST_EQUAL("Number of next nodes.", n2->nextNodes().size(), 0);

        auto n3 = NodeTypeManager::TypeOf("NodeTest3")->newInstance(p);
        auto n4 = NodeTypeManager::TypeOf("NodeTest3")->newInstance(p);
        auto n5 = NodeTypeManager::TypeOf("NodeTest3")->newInstance(p);

        n1->output() >> n3->input(0);
        n4->output() >> n3->input(1);
        n5->output() >> n3->input(2);

        KIWI_TEST_EQUAL("Number of previous nodes.", n3->previousNodes().size(), 3); 

        n3->input(0).disconnectAll();
        n3->input(1).disconnectAll();
        n3->input(2).disconnectAll();

        KIWI_TEST_EQUAL("Number of previous nodes.", n3->previousNodes().size(), 0); 

        n3->output(0) >> n4->input(0);
        n3->output(1) >> n4->input(1);
        n3->output(0) >> n5->input(0);
        
        KIWI_TEST_EQUAL("Number of next nodes.", n3->nextNodes().size(), 2); 

        printNodeLayout(n3);

        // TODO ! fails when disconnected in a different order 
        n4->input(0).disconnectAll();
        n4->input(1).disconnectAll();
        n5->input(0).disconnectAll();
        
        KIWI_TEST_EQUAL("Number of next nodes.", n3->nextNodes().size(), 0); 
        
        delete n3;
        delete n4;
        delete n5;
    }


    delete n1;
    delete n2;
    delete p;
    
    return KIWI_END_TESTING;
}
