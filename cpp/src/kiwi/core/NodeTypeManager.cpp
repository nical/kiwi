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

typedef std::map<string,NodeTypeInfo*> NodeTypeMap;

struct NodeTypeContainer
{
    NodeTypeMap map;
    ~NodeTypeContainer()
    {
        for(auto it = map.begin(); it!= map.end();++it)
            delete it->second;
    }
};

NodeTypeManager::NodeTypeManager()
{
    _types = new NodeTypeContainer;
}

NodeTypeManager::~NodeTypeManager()
{
    delete _types;
}

const NodeTypeInfo* NodeTypeManager::typeOf(const string& name)
{
    auto info = _types->map.find(name);
    if ( info == _types->map.end() )
        return 0;
    
    return info->second;
}

/**
 * Register a node type.
 */ 
const NodeTypeInfo* NodeTypeManager::registerNodeType(
    const string& nodeName
    , const NodeLayoutDescriptor& layout
    , NodeUpdater* updater )
{
    SCOPEDBLOCK("NodeTypeManager::RegisterNode");
    
    auto existing = typeOf(nodeName);
    if ( existing != 0 )
        return existing;
    
    auto info = new NodeTypeInfo;
    info->_name = nodeName;
    info->_updater = updater;
    info->_layout = layout;

    _types->map[nodeName] = info;
    return info;
}

void NodeTypeManager::unregisterAll()
{
    for(auto it = _types->map.begin(); it!= _types->map.end();++it)
            delete it->second;
    _types->map.clear();
}

void NodeTypeManager::unregister(const string& name)
{
    auto info = _types->map.find(name);
    if ( info == _types->map.end() )
        return;

    delete info->second;
    _types->map.erase( info );
}

Node* NodeTypeManager::instanciate(const string& name, Pipeline* p)
{
    auto info = typeOf(name);
    if( info != 0 )
        return info->newInstance(p);
    return 0;
}


}//namespace
}//namespace
