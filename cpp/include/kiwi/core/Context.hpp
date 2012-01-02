#pragma once
#ifndef KIWI_CORE_CONTEXT_HPP
#define KIWI_CORE_CONTEXT_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/core/DataTypeId.hpp"
#include "kiwi/core/DataHeader.hpp"

#include <map>

namespace kiwi{
namespace core{

class DataHeader;
class DataTypeManager;
class DataPool;

class Context
{
public:
    typedef std::map<DataTypeId,DataPool*> DataMap;

    Context();
    ~Context();

    static Context* DefaultContext();

    DataHeader* requestData( uint32 index );
    DataHeader* requestData( DataTypeId datatype );
    DataHeader* requestData( const DataTypeInfo* dataTypeInfo ); // deprecated

    uint32 freeData( uint32 amountHint, DataTypeId type = DataTypeId::Null );

    uint32 preallocateData( uint32 amountHint, DataTypeId type );

    void setDataTypeManager( DataTypeManager* mgr );

    /**
     * Should be called from DataHeader only.
     */ 
    void markNotUsed( DataHeader* data );
    
    uint32 id() const
    {
        return _id;
    }

    DataTypeManager * dataTypeManager() const
    {
        return _typeManager;
    }

private:
    uint32 _id;
    DataMap _data;
    DataTypeManager* _typeManager;
};



}//namespace
}//namespace


#endif
