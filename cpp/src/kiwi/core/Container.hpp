
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

    Container(const T& val, const DataTypeInfo* info)
    {
        _value = val;
        _type = info;
    }

    Container(const DataTypeInfo* info)
    {
        _type = info;
    }

    Container(string name)
    {
        _type = DataTypeManager::TypeOf(name);
    }
    
    const DataTypeInfo* type() const
    {
        return _type;
    }

    T& value()
    {
        return _value;
    }
    const T& value() const
    {
        return value;
    }
    
private:
    const DataTypeInfo* _type;
    T _value;   
};


template<typename T> T* Data::value()
{
    Container<T>* container = dynamic_cast< Container<T>* >( this );
    if ( container )
        return &container->value();
    return 0;
}

template<typename T> const T* Data::value() const
{
    Container<T>* container = dynamic_cast< Container<T>* >( this );
    if ( container )
        return &container->value();
    return 0;
}

}//namespace
}//namespace

#define KIWI_DECLARE_CONTAINER_AND_NAME( type ) kiwi::core::Data* New##type(){ return new kiwi::core::Container<type>(#type); } 
#define KIWI_DECLARE_CONTAINER( type, name ) kiwi::core::Data* New##type(){ return new kiwi::core::Container<type>(name); } 

#endif
