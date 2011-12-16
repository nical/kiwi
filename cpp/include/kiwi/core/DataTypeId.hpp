
#pragma once
#ifndef KIWI_CORE_DATATYPEID_HPP
#define KIWI_CORE_DATATYPEID_HPP

#include "kiwi/core/Commons.hpp"

namespace kiwi{
namespace core{

template<typename T>
struct TypeIdGenerator
{
    static uint32 genId()
    {
        static char addressIsTheId = 0;
        return reinterpret_cast<uint32>(&addressIsTheId);
    }
};


class DataTypeId
{
public:
    enum{ STATIC, RUNTIME, ANY };

    DataTypeId( uint32 intId, uint8 category )
    :_id(intId), _category(category)
    {
    }

    DataTypeId( const DataTypeId& toCopy )
    :_id(toCopy._id), _category(toCopy._category)
    {
    }

    template<typename T>
    static DataTypeId TypeOf()
    {
        return DataTypeId( TypeIdGenerator<T>::genId(), STATIC );
    }
    
    bool operator==(const DataTypeId& other) const
    {
        return ((other._id == _id) && (other._category == _category));
    }

    bool operator!=(const DataTypeId& other) const
    {
        return ((other._id != _id) || (other._category != _category));
    }

    bool isRuntimeType() const
    {
        return _category == RUNTIME;
    }
    
    bool isStaticType() const
    {
        return _category == STATIC;
    }

    
    
private:
    uint32  _id;
    uint8   _category; 
};


}//namespace
}//namespace

#endif
