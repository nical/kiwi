
#ifndef KIWI_CORE_NODEINTERNAL_HPP
#define KIWI_CORE_NODEINTERNAL_HPP

#include <vector>

#include "kiwi/core/ID.hpp"

namespace kiwi {
namespace core {

struct NodeInternal
{
    std::vector<std::vector<LinkID> > _inputs 
    std::vector<std::vector<LinkID> > _outputs
    NodeTypeID _nodeTypeInfo;
    NodeInternal* _next;
};

struct LinkInternal
{
    NodeID _inputNode;
    NodeID _outputNode;
    InputPortID _inputID;
    OutputPortID _outputID;
};

class NodeGroup_
{
public:
    NodeID newNode(NodeTypeID type);
    
private:
};


} // namespace
} // namespace

#endif
