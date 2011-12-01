
#pragma once

#ifndef KIWI_CORE_TYPEID
#define KIWI_CORE_TYPEID

#include "kiwi/core/Commons.hpp"

namespace kiwi{
namespace core{

typedef kiwi::uint32 TypeID;


template< typename T >
struct TypeIdGenerator
{
private: TypeIdGenerator(){}
public:
	static TypeID GetTypeId()
	{
        static char addressOfThisIsTheTypeId;
		return reinterpret_cast< TypeID >( &addressOfThisIsTheTypeId );
	}
};

// qualifier stripping
template< typename T >
struct TypeIdGenerator< const T >
{
private: TypeIdGenerator(){}
public:
    static TypeID GetTypeId()
	{
        return TypeIdGenerator<T>::GetTypeId();
	}
};
template< typename T >
struct TypeIdGenerator< volatile T >
{
private: TypeIdGenerator(){}
public:
    static TypeID GetTypeId()
	{
        return TypeIdGenerator<T>::GetTypeId();
	}
};

// -----------------------------------------------------------------------------

template <typename T> TypeID TypeOf(const T&)
{
    return TypeIdGenerator<T>::GetTypeId();
}

template <typename T> TypeID TypeOf()
{
    return TypeIdGenerator<T>::GetTypeId();
}



}//namespace
}//namespace

#endif 
