
#pragma once
#ifndef KIWI_CORE_DATATYPEMANAGER_HPP
#define KIWI_CORE_DATATYPEMANAGER_HPP

#include "kiwi/core/Data.hpp"




namespace kiwi{
namespace core{

namespace DataTypeManager{

    const DataTypeInfo* RegisterDataType(string uniqueName, DataTypeInfo::Instanciator instanciator);

    const DataTypeInfo* TypeOf(string name);

    Data* Create(string name);

}//namespace


}//namespace
}//namespace

#endif
