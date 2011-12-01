

#include "kiwi/utils/TypeIdHelper.hpp"


#include <map>

namespace kiwi{
namespace utils{

static std::map<kiwi::core::TypeID,string> _typeNames;
static string _unknownTypeName;
static int _isInit = 0;

static void InitHelper()
{
    _typeNames[0] = "InvalidType";
    _unknownTypeName = "UnknownType";
    _isInit = 1;
}

const string& TypeIdName( kiwi::core::TypeID id )
{
    auto it = _typeNames.find(id);
    if ( it != _typeNames.end() )
        return it->second;
    else
        return _unknownTypeName;
}

void RegisterTypeIdName( kiwi::core::TypeID id, const string& name )
{
    if (!_isInit) InitHelper();
    if(id == 0) return;
    _typeNames[id] = name;
}


}//namespace
}//namespace
