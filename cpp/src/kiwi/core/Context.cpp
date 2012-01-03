
#include "kiwi/core/Context.hpp"
#include "kiwi/core/DataTypeManager.hpp"
#include "kiwi/core/NodeTypeManager.hpp"
//#include "kiwi/core/DataPool.hpp"


namespace kiwi{

// to pass by default context in default parameter without having to include
// Context.hpp in too many headers
kiwi::core::Context& DefaultContext()
{
    return core::Context::Default();
}

namespace core{

Context::Context()
{
    setDataTypeManager( new DataTypeManager );
    setNodeTypeManager( new NodeTypeManager );
}

Context::~Context()
{

}

static Context s_defaultContext;

Context& Context::Default()
{
    return s_defaultContext;
}

DataHeader * Context::requestData( DataTypeId type )
{
    /*
    DataHeader* temp = _data[type]->pop();
    if (temp) return temp;
    return _typeManager->createInstance(type);
    */
    return 0;
}

DataHeader * Context::requestData( uint32 type )
{
    // if ( contains(type) )
    return 0;
}

/*
uint32 Context::freeData( uint32 amountHint, DataTypeId type )
{
    return 0;
}

uint32 Context::preallocateData( uint32 amountHint, DataTypeId type )
{    
    return 0;
}
*/
void Context::setDataTypeManager( DataTypeManager * mgr )
{
    assert( mgr );
    _dataTypeManager = mgr;
}
void Context::setNodeTypeManager( NodeTypeManager * mgr )
{
    assert( mgr );
    _nodeTypeManager = mgr;
}

/**
 * Should be called from DataHeader only.
 */ 
void Context::markNotUsed( DataHeader * data )
{
    
}


const DataTypeInfo* Context::registerDataType(const string& uniqueName, DataInstanciator instanciator)
{
    return _dataTypeManager->registerDataType(uniqueName, instanciator);
}

const DataTypeInfo* Context::dataTypeInfo(const string& name)
{
    return _dataTypeManager->typeOf(name);
}

Data* Context::instanciateData(const string& name)
{
    return _dataTypeManager->instanciate(name);
}

const NodeTypeInfo* Context::registerNodeType(
        const string& nodeName
        , const NodeLayoutDescriptor& layout
        , NodeUpdater* updater )
{
    return _nodeTypeManager->registerNodeType(nodeName, layout, updater);
}

const NodeTypeInfo* Context::nodeTypeInfo(const string& name)
{
    return _nodeTypeManager->typeOf(name);
}

/*
Node* Context::instanciateNode(const string& name)
{
    return _nodeTypeManager->instanciate(name);
}
*/

}//namespace
}//namespace
