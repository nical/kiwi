
#pragma once
#ifndef KIWI_CORE_DATATYPEMANAGER_HPP
#define KIWI_CORE_DATATYPEMANAGER_HPP

#include "kiwi/core/Data.hpp"

namespace kiwi{
namespace user{

template<typename DataType > struct DataTrait
{
    static const char* Name(){return "Error";}
};

}//namespace
}//namespace

namespace kiwi{
namespace core{

const DataTypeInfo* RegisterDataType(string uniqueName, DataTypeInfo::Instanciator instanciator);
const DataTypeInfo* TypeOf(string name);
Data* InstanciateData(string name);


}//namespace
}//namespace

#endif
