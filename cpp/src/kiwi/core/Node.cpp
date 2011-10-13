
#include "kiwi/core/Node.hpp"
#include "kiwi/core/InputPort.hpp"
#include "kiwi/core/OutputPort.hpp"
#include "kiwi/core/Data.hpp"
#include "kiwi/core/CompatibilityStrategy.hpp"
#include "kiwi/core/DataStrategy.hpp"

namespace kiwi{
namespace core{

Node::Node(Pipeline* pipeline, NodeInitializer& init)
{
    _pipeline = pipeline;
    if(pipeline) pipeline->addNode(this);
    _id = _newId();
    for(int i = 0; i < init.ports.size(); ++i)
    {
        if( (init.ports[i].flags & IN) && (init.ports[i].flags & OUT) ) // in+out port
        {
            log.error() << "in+out ports not implemented yet.\n";
        }
        else if( init.ports[i].flags & IN )
        {
            _inputs.push_back(
                new InputPort(this, init.ports[i].type, init.ports[i].flags)
            );
        }
        else if( init.ports[i].flags & OUT )
        {
            _outputs.push_back(
                new OutputPort(this,
                    new AutoDataStrategy(init.ports[i].type), init.ports[i].flags)
            );
        }
    }
}




}//namespace
}//namespace
