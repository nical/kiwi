
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


// implementation from
// http://altdevblogaday.com/2011/10/10/making-your-own-type-id-is-fun/

// WARNING: not thread safe !
template< typename T >
class DataTypeIdGenerator
{
private:
    // no instance of this class can be created.
    DataTypeIdGenerator(){}
public:
    // this generates a typeID for each class that instantiates the template
    static Data::TypeId GetTypeId()
    {
        // I wasn't sure if the char would take up > 1 byte because of alignment.
        // With VS2010 on win32 they take up exactly 1 byte each (and in the pastebin too...)
        static char chAddressOfThisIsTheTypeId;
        return reinterpret_cast< Data::TypeId >( &chAddressOfThisIsTheTypeId );
    }
};

// template specialisation to disgard constness
template< typename T >
class DataTypeIdGenerator< const T >
{
private:
    DataTypeIdGenerator(){}
public:
    static Data::TypeId GetTypeId()
    {
        DataTypeIdGenerator<T>::GetTypeId();
    }
};


template<class T> Data::TypeId DataTypeId(){ return DataTypeIdGenerator<T>::GetTypeId(); }
template<class T> Data::TypeId DataTypeId(const T&){ return DataTypeIdGenerator<T>::GetTypeId(); }

}//namespace
}//namespace

#endif
