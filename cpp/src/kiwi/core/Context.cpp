
#include "kiwi/core/Context.hpp"
#include "kiwi/core/DataTypeManager.hpp"
//#include "kiwi/core/DataPool.hpp"


namespace kiwi{
namespace core{

Context::Context()
{

}

Context::~Context()
{

}

static Context s_defaultContext;

Context * Context::DefaultContext()
{
    return &s_defaultContext;
}

DataHeader * Context::requestData( DataTypeId type )
{
    /*
    DataHeader* temp = _data[type]->pop();
    if (temp) return temp;
    return _typeManager->createInstance(type);
    */ 
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


}//namespace
}//namespace
