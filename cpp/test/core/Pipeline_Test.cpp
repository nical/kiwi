
#include "kiwi/core/Pipeline.hpp"
#include "kiwi/core/Commons.hpp"
#include "kiwi/utils/Testing.hpp"
#include "kiwi/core/Node.hpp"
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
bool func1(DataArray& inputs, DataArray& outputs)
{
    SCOPEDBLOCK("func1");
    updates.push_back(1);
    return true;
}

bool func2(DataArray& inputs, DataArray& outputs)
{
    SCOPEDBLOCK("func2");
    updates.push_back(2);
    return true;
}

bool func3(DataArray& inputs, DataArray& outputs)
{
    SCOPEDBLOCK("func3");
    updates.push_back(3);
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
        { "in0", IntInfo, READ },
        { "in1", IntInfo, READ }
    };
    layout1.outputs = {
        { "out0", IntInfo, READ },
        { "out1", IntInfo, READ }
    };

    Pipeline pipeline( new ProcessingPipelineUpdater(), 0, 0 );

    auto n1 = mock::NewMockNode();
    assert( n1 != 0 );
    pipeline.update();
    
    return KIWI_END_TESTING
}
