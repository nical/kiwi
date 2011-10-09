
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
    Container()
    {
        _type = core::TypeOf( user::DataTrait<T>::Name() );
    }
    
    const DataTypeInfo* type() const
    {
        return _type;
    }
    
private:
    const DataTypeInfo* _type;    
};

}//namespace
}//namespace

#endif
