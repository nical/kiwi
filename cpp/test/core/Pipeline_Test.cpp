
#include "kiwi/core/DataTypeManager.hpp"
#include "kiwi/core/Pipeline.hpp"
#include "kiwi/core/Commons.hpp"
#include "kiwi/utils/Testing.hpp"
#include "kiwi/core/Node.hpp"
#include "kiwi/core/OpConnect.hpp"
#include "kiwi/core/NodeTypeManager.hpp"
#include "kiwi/processing/ProcessingPipelineUpdater.hpp"
#include "kiwi/mock/MockNode.hpp"
#include "kiwi/core/DynamicNodeUpdater.hpp"

using namespace kiwi;
using namespace kiwi::core;
using namespace kiwi::processing;

//KIWI_DECLARE_CONTAINER(int,"Int");

std::vector<int> updates;

typedef DynamicNodeUpdater::DataArray DataArray;
bool func1(const DataArray& inputs, const DataArray& outputs)
{
    SCOPEDBLOCK("func1");
    updates.push_back(1);
    return true;
}

bool func2(const DataArray& inputs, const DataArray& outputs)
{
    SCOPEDBLOCK("func2");
    updates.push_back(2);
    return true;
}

bool func3(const DataArray& inputs, const DataArray& outputs)
{
    SCOPEDBLOCK("func3");
    updates.push_back(3);
    return true;
}


bool func4(const DataArray& inputs, const DataArray& outputs)
{
    SCOPEDBLOCK("func4");
    updates.push_back(4);
    return true;
}

bool func5(const DataArray& inputs, const DataArray& outputs)
{
    SCOPEDBLOCK("func5");
    updates.push_back(5);
    return true;
}

int main()
{
    KIWI_BEGIN_TESTING("kiwi::core::Pipeline")

    mock::DeclareMockNode(3,3);


    //auto IntInfo = DataTypeManager::RegisterDataType("Int", &Newint);
    auto IntInfo = DataTypeManager::TypeOf("Int");
    

    NodeLayoutDescriptor layout1;
    layout1.inputs = {
        { "in0", IntInfo, READ|OPT },
        { "in1", IntInfo, READ|OPT }
    };
    layout1.outputs = {
        { "out0", IntInfo, READ },
        { "out1", IntInfo, READ }
    };

    NodeTypeManager::RegisterNode("N1",layout1, new DynamicNodeUpdater(&func1));
    NodeTypeManager::RegisterNode("N2",layout1, new DynamicNodeUpdater(&func2));
    NodeTypeManager::RegisterNode("N3",layout1, new DynamicNodeUpdater(&func3));
    NodeTypeManager::RegisterNode("N4",layout1, new DynamicNodeUpdater(&func4));
    NodeTypeManager::RegisterNode("N5",layout1, new DynamicNodeUpdater(&func5));

    Pipeline pipeline( &DefaultContext(), new ProcessingPipelineUpdater() );

    auto n1 = NodeTypeManager::Create("N1");
    auto n2 = NodeTypeManager::Create("N2");
    auto n3 = NodeTypeManager::Create("N3");
    auto n4 = NodeTypeManager::Create("N4");
    auto n5 = NodeTypeManager::Create("N5");
    
    assert( n1 != 0 );
    assert( n2 != 0 );
    assert( n3 != 0 );

    pipeline.addNode(n1);
    pipeline.addNode(n2);
    pipeline.addNode(n3);

    n1->output(0) >> n2->input(0);
    n2->output(0) >> n3->input(0);

    KIWI_TEST_EQUAL("Number of nodes in the pipeline", pipeline.nodes().size(), 3 );
    
    pipeline.update();
    
    
    KIWI_TEST_EQUAL("Number of nodes executed", updates.size(), 3 );
    
    KIWI_TEST("Order of execution", updates == std::vector<int>({1,2,3}));

    for(uint32 i = 0; i < updates.size(); ++i )
    {
        log << " " << updates[i];
    }

    pipeline.addNode(n4);
    pipeline.addNode(n5);

    n4->output(0) >> n2->input(1);
    n5->output(0) >> n3->input(1);
    
    updates.clear();

    pipeline.update();

    
    for(uint32 i = 0; i < updates.size(); ++i )
    {
        log << " " << updates[i];
    }

    
    return KIWI_END_TESTING
}
