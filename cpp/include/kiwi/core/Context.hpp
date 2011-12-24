#pragma once
#ifndef KIWI_CORE_CONTEXT_HPP
#define KIWI_CORE_CONTEXT_HPP

#include "kiwi/core/Commons.hpp"
#include "kiwi/core/DataTypeId.hpp"

namespace kiwi{
namespace core{

class DataHeader;
class DataTypeManager;

class Context
{
public:
    Context();
    ~Context();

    static Context * DefaultContext();

    DataHeader * requestData( DataTypeId type );

    uint32 freeData( uint32 amountHint, DataTypeId type = DataTypeId::Null );

    uint32 preallocateData( uint32 amountHint, DataTypeId type );

    void setTypeManager( DataTypeManager * mgr );

    /**
     * Should be called from DataHeader only.
     */ 
    void markNotUsed( DataHeader * data );
    
    uint32 id() const
    {
        return _id;
    }

private:
    uint32 _id;
};



}//namespace
}//namespace


#endif
