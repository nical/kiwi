
#include "kiwi/core/Data.hpp"
#include "kiwi/core/DataTypeManager.hpp"
#include "kiwi/core/NodeTypeManager.hpp"
#include "kiwi/core/Commons.hpp"

#include <map>

namespace kiwi{
namespace core{

    
typedef std::map<string, DataTypeInfo*> DataTypeMap;
static std::map<string, DataTypeInfo*> _types;


const DataTypeInfo* DataTypeManager::RegisterDataType(string name, DataTypeInfo::Instanciator instanciator)
{
    //DataTypeInfo(string dataName, SubDataArray subdata, Instanciator instanciator)
    const DataTypeInfo* result = TypeOf(name);
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

const DataTypeInfo* DataTypeManager::TypeOf(string name)
{
    DataTypeMap::iterator info = _types.find(name);
    if ( info == _types.end() )
        return 0;
    
    return info->second;
}

Data* DataTypeManager::Create(string name)
{
    const DataTypeInfo* info = TypeOf( name );
    if ( info== 0 )
        return 0;
    return info->newInstance();
}


const DataTypeInfo* KIWI_DTM_TypeOf(string name)
{
    return DataTypeManager::TypeOf(name);
}

}//namespace
}//namespace
