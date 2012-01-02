
#include "kiwi/core/Data.hpp"
#include "kiwi/core/DataTypeManager.hpp"
#include "kiwi/core/NodeTypeManager.hpp"
#include "kiwi/core/Commons.hpp"
#include "kiwi/core/Context.hpp"

#include <map>

namespace kiwi{
namespace core{

typedef std::map<string, DataTypeInfo*> DataTypeMap;

struct DataTypeContainer
{
    DataTypeMap map;
    ~DataTypeContainer()
    {
        for(auto it = map.begin(); it!= map.end();++it)
            delete it->second;
    }
};

DataTypeManager::DataTypeManager()
{
    _types = new DataTypeContainer;
}

DataTypeManager::~DataTypeManager()
{
    delete _types;
}

const DataTypeInfo* DataTypeManager::registerDataType(
    const string& name
    , DataTypeInfo::Instanciator instanciator)
{
    const DataTypeInfo* result = typeOf(name);
    if ( result != 0 )
        return result;

    DataTypeInfo::SubDataArray dummy;
    DataTypeInfo* newInfo = new DataTypeInfo(name, dummy, instanciator);
    _types->map[name] = newInfo;

    // register a container node for this data type
    NodeLayoutDescriptor containerNodeDesc;
    containerNodeDesc.outputs = { { "data", newInfo, READ } };
    DefaultContext().nodeTypeManager().registerNodeType( name, containerNodeDesc, 0 );
    
    return newInfo;
}

const DataTypeInfo* DataTypeManager::typeOf(const string& name)
{
    DataTypeMap::iterator info = _types->map.find(name);
    if ( info == _types->map.end() )
        return 0;
    
    return info->second;
}

Data* DataTypeManager::instanciate(const string& name)
{
    const DataTypeInfo* info = typeOf( name );
    if ( info== 0 )
        return 0;
    return info->newInstance();
}


const DataTypeInfo* Kiwi_DTM_TypeOf(string name)
{
    return DefaultContext().dataTypeInfo( name );
}



}//namespace
}//namespace
