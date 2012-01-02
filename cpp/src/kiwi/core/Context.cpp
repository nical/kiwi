
#include "kiwi/core/Context.hpp"
#include "kiwi/core/DataTypeManager.hpp"
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

uint32 Context::freeData( uint32 amountHint, DataTypeId type )
{
    return 0;
}

uint32 Context::preallocateData( uint32 amountHint, DataTypeId type )
{    
    return 0;
}

void Context::setDataTypeManager( DataTypeManager * mgr )
{
    _typeManager = mgr;
}

/**
 * Should be called from DataHeader only.
 */ 
void Context::markNotUsed( DataHeader * data )
{
    
}


const DataTypeInfo* Context::registerDataType(const string& uniqueName, DataInstanciator instanciator)
{
    return _typeManager->registerDataType(uniqueName, instanciator);
}

const DataTypeInfo* Context::dataTypeInfo(const string& name)
{
    return _typeManager->typeOf(name);
}

Data* Context::instanciateData(const string& name)
{
    return _typeManager->create(name);
}


}//namespace
}//namespace
