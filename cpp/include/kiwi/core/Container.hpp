
#pragma once
#ifndef KIWI_CORE_CONTAINER_HPP
#define KIWI_CORE_CONTAINER_HPP

#include "kiwi/core/Data.hpp"
#include "kiwi/core/Commons.hpp"

namespace kiwi{
namespace core{

class DataTypeInfo;
namespace DataTypeManager{
    const DataTypeInfo* TypeOf(string name);
} 


///**
 //* Templated wrapper for data.
 //*
 //* Contains the data of an output port (inherits from kiwi::core::Data).
 //*/ 
//template<typename T> class Container //: public Data
//{
//public:
    //// TODO one should not need to pass the type info to the constructor as the
    //// later cannot check that the type info corresponds to the template parameter.
    //Container(const T& val, const DataTypeInfo* info)
    //{
        //_value = val;
        //_type = info;
    //}
    
    //// TODO one should not need to pass the type info to the constructor as the
    //// later cannot check that the type info corresponds to the template parameter.
    //Container(const DataTypeInfo* info)
    //{
        //_type = info;
    //}
    
    //// TODO one should not need to pass the type info to the constructor as the
    //// later cannot check that the type info corresponds to the template parameter.
    //Container(string name)
    //{
        //_type = kiwi::core::DataTypeManager::TypeOf(name);
    //}

    ///**
     //* Returns the runtime type info;
     //*/ 
    //const DataTypeInfo* type() const
    //{
        //return _type;
    //}

    ///**
     //* Returns the wrapped data.
     //*/ 
    //T& value()
    //{
        //return _value;
    //}

    ///**
     //*Returns the wrapped data (const).
     //*/ 
    //const T& value() const
    //{
        //return value;
    //}
    
//private:
    //const DataTypeInfo* _type;
    //T _value;   
//};


//template<typename T> T* Data::value()
//{
    //Container<T>* container = dynamic_cast< Container<T>* >( this );
    //if ( container )
        //return &container->value();
    //return 0;
//}

//template<typename T> const T* Data::value() const
//{
    //Container<T>* container = dynamic_cast< Container<T>* >( this );
    //if ( container )
        //return &container->value();
    //return 0;
//}

}//namespace
}//namespace

#endif
