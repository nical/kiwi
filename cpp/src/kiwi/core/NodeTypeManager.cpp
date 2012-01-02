#include "kiwi/core/NodeTypeManager.hpp"
#include "kiwi/core/Node.hpp"

#include <map>

namespace kiwi{
namespace core{



Node* NodeTypeInfo::newInstance(Pipeline* p) const
{
    return new Node(p, this);
}


// -----------------------------------------------------------------------------


static std::map<string,NodeTypeInfo*> _types;

NodeTypeManager::NodeTypeIterator Types_begin()
{
    return _types.begin();
}
    
NodeTypeManager::NodeTypeIterator Types_end()
{
    return _types.end();
}

const NodeTypeInfo* NodeTypeManager::_RegisterNode( string nodeName
    , const NodeLayoutDescriptor& layout, NodeUpdater* updater )
{
    SCOPEDBLOCK("NodeTypeManager::RegisterNode");
    
    auto existing = _TypeOf(nodeName);
    if ( existing != 0 )
        return existing;
    
    auto info = new NodeTypeInfo;
    info->_name = nodeName;
    info->_updater = updater;
    info->_layout = layout;

    _types[nodeName] = info;
    return info;
}

void NodeTypeManager::_Unregister(string name)
{
    auto info = _types.find(name);
    if ( info == _types.end() )
        return;

    delete info->second;
    _types.erase( info );
}

void NodeTypeManager::_UnregisterAll()
{
    _types.clear();
}

const NodeTypeInfo* NodeTypeManager::_TypeOf(string name)
{
    auto info = _types.find(name);
    if ( info == _types.end() )
        return 0;
    
    return info->second;
}

Node* NodeTypeManager::_Create(string name, Pipeline* p)
{
    auto info = _TypeOf(name);
    if( info != 0 )
        return info->newInstance(p);
    return 0;
}




}//namespace
}//namespace
