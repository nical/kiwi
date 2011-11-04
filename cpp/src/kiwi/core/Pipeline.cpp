
#include "kiwi/core/Pipeline.hpp"
#include "kiwi/core/Node.hpp"

namespace kiwi{
namespace core{

void Pipeline::setNodePipeline(Node* n, Pipeline* p)
{
    n->_pipeline = p;
}

Pipeline::Pipeline()
{
    _id = _newId();
}

Pipeline::~Pipeline()
{
    removeAllNodes();

    if ( _updater ) delete _updater;
    if ( _optimizer ) delete _optimizer;
}


bool Pipeline::setInput(uint32 index, Data* inputData)
{
    return false;
}

bool Pipeline::setOutput(uint32 index, Data* inputData)
{
    return false;
}

bool Pipeline::addNode( Node* n )
{
    return false;
}

bool Pipeline::removeNode( Node* n )
{
    return false;
}
bool Pipeline::removeAllNodes()
{
    return false;
}

bool Pipeline::contains(const Node* n)
{
    return false;
}

}//namespace
}//namespace
