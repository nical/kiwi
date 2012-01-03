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
class NodeTypeManager;
class NodeTypeInfo;
class NodeUpdater;
class DataPool;
class Data;
class Node;
class NodeLayoutDescriptor;

class Context
{
public:
    typedef std::map<DataTypeId,DataPool*> DataMap;
    typedef Data* (*DataInstanciator)();
    
    Context();
    ~Context();

    static Context& Default();

    // ----
    /**
     * cf. DataTypeManager
     */ 
    const DataTypeInfo* registerDataType(const string& uniqueName, DataInstanciator instanciator);

    const DataTypeInfo* dataTypeInfo(const string& name);

    Data* instanciateData(const string& name);

    /**
     * cf. NodeTypeManager
     */ 
    const NodeTypeInfo* registerNodeType(
        const string& nodeName
        , const NodeLayoutDescriptor& layout
        , NodeUpdater* updater );
        
    const NodeTypeInfo* nodeTypeInfo(const string& name);
    // ----
    

    DataHeader* requestData( uint32 index );
    DataHeader* requestData( DataTypeId datatype );
    DataHeader* requestData( const DataTypeInfo* dataTypeInfo ); // deprecated

    

    void setDataTypeManager( DataTypeManager* mgr );
    void setNodeTypeManager( NodeTypeManager* mgr );

    /**
     * Should be called from DataHeader only.
     */ 
    void markNotUsed( DataHeader* data );
    
    uint32 id() const
    {
        return _id;
    }

    DataTypeManager& dataTypeManager() const
    {
        assert( _dataTypeManager );
        return *_dataTypeManager;
    }

    NodeTypeManager& nodeTypeManager() const
    {
        assert( _nodeTypeManager );
        return *_nodeTypeManager;
    }

private:
    uint32 _id;
    DataMap _data;
    DataTypeManager* _dataTypeManager;
    NodeTypeManager* _nodeTypeManager;
};



}//namespace
}//namespace


#endif
