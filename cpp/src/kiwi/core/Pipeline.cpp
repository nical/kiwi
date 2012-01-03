
#include "kiwi/core/Pipeline.hpp"
#include "kiwi/core/Node.hpp"
#include "kiwi/core/Context.hpp"
#include "kiwi/core/NodeTypeManager.hpp"

namespace kiwi{
namespace core{

void Pipeline::setNodePipeline(Node* n, Pipeline* p)
{
    n->_pipeline = p;
}

Pipeline::~Pipeline()
{
    removeAllNodes();

    if ( _updater ) delete _updater;
}


bool Pipeline::setInput(uint32 index, Data* inputData)
{
    KIWI_NOT_IMPLEMENTED("Pipeline::setInput");
    return false;
}

bool Pipeline::setOutput(uint32 index, Data* inputData)
{
    KIWI_NOT_IMPLEMENTED("Pipeline::setOutput");
    return false;
}

bool Pipeline::addNode( Node* n )
{
    if(!contains(n))
    {
        _nodes.push_back(n);
        return true;
    }
    else
    {
        return false;
    }
}

static int _findIndexOf( Pipeline::NodeArray nodes, const Node* n )
{
    for(uint32  i=0; i < nodes.size(); ++i)
        if(nodes[i] == n)
             return i;
    return -1;
}

bool Pipeline::removeNode( Node* n )
{
    log << "Pipeline::removeNode" << endl;
    int idx = _findIndexOf(_nodes, n);
    if ( idx > 0 )
    {
        delete n;
        _nodes[idx] = _nodes[_nodes.size()-1];
        _nodes.resize(_nodes.size()-1);
        return true;
    }
    return false;
}
bool Pipeline::removeAllNodes()
{
    for(uint32 i = 0; i < _nodes.size(); ++i )
        delete _nodes[i];
    _nodes.resize(0);
    return true;
}

bool Pipeline::contains(const Node* n)
{
    int idx = _findIndexOf(_nodes, n);
    return idx > 0;
}


Node * Pipeline::instanciateNode(const string& name)
{
    return _context->nodeTypeManager().instanciate(name, this);
}

}//namespace
}//namespace
