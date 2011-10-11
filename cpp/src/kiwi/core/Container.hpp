
#pragma once
#ifndef KIWI_CORE_CONTAINER_HPP
#define KIWI_CORE_CONTAINER_HPP

#include "kiwi/core/Data.hpp"
#include "kiwi/core/DataTypeManager.hpp"

namespace kiwi{
namespace core{


template<typename T> class Container : public Data
{
public:
    Container(string name)
    {
        _type = core::TypeOf( name );
    }
    
    const DataTypeInfo* type() const
    {
        return _type;
    }

    Data::TypeId dataTypeId() const
    {
        return DataTypeId<T>();
    }
    
private:
    const DataTypeInfo* _type;    
};

}//namespace
}//namespace

#define KIWI_DECLARE_CONTAINER_AND_NAME( type ) kiwi::core::Data* New##type(){ return new kiwi::core::Container<type>(#type); } 
#define KIWI_DECLARE_CONTAINER( type, name ) kiwi::core::Data* New##type(){ return new kiwi::core::Container<type>(name); } 

#endif
