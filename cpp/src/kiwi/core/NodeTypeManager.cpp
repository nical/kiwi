#include "kiwi/core/NodeTypeManager.hpp"
#include "kiwi/core/NodeTypeManager.hpp"
#include "kiwi/core/Node.hpp"

#include <map>

namespace kiwi{
namespace core{


static std::map<string,NodeTypeInfo*> _types;


Node* NodeTypeInfo::newInstance(Pipeline* p) const
{
    return new Node(p, this);
}

const NodeTypeInfo* NodeTypeManager::RegisterNode( string nodeName
    , const NodeLayoutDescriptor& layout, NodeUpdater* updater )
{
    auto existing = TypeOf(nodeName);
    if ( existing != 0 )
        return existing;
    
    auto info = new NodeTypeInfo;
    info->_name = nodeName;
    info->_layout = layout;
    info->_updater = updater;

    _types[nodeName] = info;
    return info;
}

void NodeTypeManager::Unregister(string name)
{
    // TODO
}

void NodeTypeManager::UnregisterAll()
{
    // TODO
}

const NodeTypeInfo* NodeTypeManager::TypeOf(string name)
{
    auto info = _types.find(name);
    if ( info == _types.end() )
        return 0;
    
    return info->second;
}

Node* NodeTypeManager::Create(string name)
{
    auto info = TypeOf(name);
    if( info != 0 )
        return info->newInstance();
    return 0;
}




}//namespace
}//namespace
