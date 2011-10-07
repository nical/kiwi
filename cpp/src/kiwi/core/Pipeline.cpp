
#include "kiwi/core/Pipeline.hpp"
#include "kiwi/core/Node.hpp"

namespace kiwi{
namespace core{

void Pipeline::setNodePipeline(Node* n, Pipeline* p)
{
    n->_pipeline = p;
}

Pipeline::~Pipeline()
{

}


}//namespace
}//namespace
