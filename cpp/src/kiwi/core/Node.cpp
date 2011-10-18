
#include "kiwi/core/Node.hpp"
#include "kiwi/core/InputPort.hpp"
#include "kiwi/core/OutputPort.hpp"
#include "kiwi/core/Data.hpp"
#include "kiwi/core/CompatibilityStrategy.hpp"
#include "kiwi/core/NodeTypeManager.hpp"
#include "kiwi/core/DataStrategy.hpp"
#include "kiwi/core/NodeUpdater.hpp"

namespace kiwi{
namespace core{

Node::Node(Pipeline* pipeline, const NodeTypeInfo* typeInfo)
{
    _pipeline = pipeline;
    if(pipeline) pipeline->addNode(this);
    _id = _newId();
    _updater = typeInfo->_updater;
    
    for(int i = 0; i < typeInfo->inputs().size(); ++i)
    {
        _inputs.push_back(
            new InputPort( this
                , typeInfo->outputs()[i].dataType 
                , typeInfo->outputs()[i].accessFlags )
        );
    }
    
    for(int i = 0; i < typeInfo->outputs().size(); ++i)
    {
        _outputs.push_back(
            new OutputPort( this
                , new AutoDataStrategy( typeInfo->outputs()[i].dataType )
                , typeInfo->outputs()[i].accessFlags )
        );
    }
}

void Node::update()
{
    if (_updater)
        _updater->update(*this);
}



}//namespace
}//namespace
