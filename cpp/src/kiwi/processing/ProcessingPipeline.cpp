
#include "kiwi/core/Node.hpp"
#include "kiwi/processing/ProcessingPipeline.hpp"

namespace kiwi{
namespace processing{


bool ProcessingPipeline::addNode(core::Node* n)
{
    _nodes.push_back(n);
    setNodePipeline(n,this);
    return true;
}

bool ProcessingPipeline::update()
{
    return false;
}

}//namespace
}//namespace
