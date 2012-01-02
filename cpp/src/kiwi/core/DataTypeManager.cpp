
#include "kiwi/core/Data.hpp"
#include "kiwi/core/DataTypeManager.hpp"
#include "kiwi/core/NodeTypeManager.hpp"
#include "kiwi/core/Commons.hpp"

#include <map>

namespace kiwi{
namespace core{
    
typedef std::map<string, DataTypeInfo*> DataTypeMap;
static DataTypeMap _types;


const DataTypeInfo* DataTypeManager::_RegisterDataType(string name, DataTypeInfo::Instanciator instanciator)
{
    //DataTypeInfo(string dataName, SubDataArray subdata, Instanciator instanciator)
    const DataTypeInfo* result = DataTypeManager::_TypeOf(name);
    if ( result != 0 )
        return result;

    DataTypeInfo::SubDataArray dummy;
    DataTypeInfo* newInfo = new DataTypeInfo(name, dummy, instanciator);
    _types[name] = newInfo;

    // register a container node for this data type
    NodeLayoutDescriptor containerNodeDesc;
    containerNodeDesc.outputs = { { "data", newInfo, READ } };
    NodeTypeManager::RegisterNode( name, containerNodeDesc, 0 );
    
    return newInfo;
}

const DataTypeInfo* DataTypeManager::_TypeOf(string name)
{
    DataTypeMap::iterator info = _types.find(name);
    if ( info == _types.end() )
        return 0;
    
    return info->second;
}

Data* DataTypeManager::Create(string name)
{
    const DataTypeInfo* info = DataTypeManager::_TypeOf( name );
    if ( info== 0 )
        return 0;
    return info->newInstance();
}

const DataTypeInfo* Kiwi_DTM_TypeOf(string name)
{
    return DataTypeManager::_TypeOf( name );
}



}//namespace
}//namespace
