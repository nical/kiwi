
#include "kiwi/core/Algorithm.hpp"
#include "kiwi/core/Node.hpp"
#include "kiwi/core/InputPort.hpp"
#include "kiwi/core/OutputPort.hpp"
#include "kiwi/core/OpConnect.hpp"
#include "kiwi/core/DataTypeManager.hpp"
#include "kiwi/core/NodeTypeManager.hpp"
#include "kiwi/core/Commons.hpp"
#include "kiwi/utils/Testing.hpp"
#include "kiwi/utils/DebugStream.hpp"
#include "kiwi/core/DynamicNodeUpdater.hpp"
#include "kiwi/core/Data.hpp"


using namespace kiwi;
using namespace kiwi::core;

KIWI_DECLARE_CONTAINER(int,"Int")

bool TestFunction(
      const DynamicNodeUpdater::DataArray& inputs
    , const DynamicNodeUpdater::DataArray& outputs )
{
    SCOPEDBLOCK("TestFunction");
    
    int a = *inputs[0]->value<int>();
    int b = *inputs[1]->value<int>();

    int& c = *outputs[0]->value<int>();
    c = a + b;
    
    return true;
}

int main()
{
    KIWI_BEGIN_TESTING("Kiwi::core::Algorithm");
 
    // declare data types
    auto IntInfo = DataTypeManager::RegisterDataType("Int", &Newint);

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

    NodeTypeManager::RegisterNode("MyNode1", layout1
        , new DynamicNodeUpdater(&TestFunction) );

    auto n = NodeTypeManager::Create("MyNode1");

    auto in1 = NodeTypeManager::Create("Int");
    auto in2 = NodeTypeManager::Create("Int");

    assert( in1->output().data() != 0 );
    assert( in1->output().data()->value<int>() != 0 );

    *in1->output().data()->value<int>() = 42;
    *in2->output().data()->value<int>() = 1337;

    KIWI_TEST( "DynamicNodeUpdater update.", !n->update() );

    assert( in1->output() >> n->input(0) );
    assert( in2->output() >> n->input(1) );

    KIWI_TEST( "DynamicNodeUpdater update.", n->update() );


    KIWI_TEST( "Update result.", *n->output().data()->value<int>() == 1337+42 );


    return KIWI_END_TESTING;
}

