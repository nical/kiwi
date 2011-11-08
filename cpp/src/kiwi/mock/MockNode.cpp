
#include "kiwi/mock/MockNode.hpp"
#include "kiwi/core/Node.hpp"
#include "kiwi/core/NodeTypeManager.hpp"
#include "kiwi/core/DataTypeManager.hpp"
#include "kiwi/mock/MockNodeUpdater.hpp"

using namespace kiwi::core;

namespace kiwi{
namespace mock{

static const NodeTypeInfo* _mockNodeInfo;

KIWI_DECLARE_CONTAINER(int,"Int");

void DeclareMockNode( uint32 nbInputs, uint32 nbOutputs )
{
    auto IntInfo = DataTypeManager::RegisterDataType("Int", &Newint);

    NodeLayoutDescriptor layout;

    for(int i = 0; i < nbInputs; ++i)
        layout.inputs.push_back( { "in", IntInfo, READ } );

    for(int i = 0; i < nbInputs; ++i)
        layout.outputs.push_back( { "out", IntInfo, READ } );
    

    _mockNodeInfo = NodeTypeManager::RegisterNode(
        "MockNode", layout, new mock::MockNodeUpdater
    );

}

core::Node* NewMockNode()
{
    return _mockNodeInfo->newInstance();
}




}//namespace
}//namespace
