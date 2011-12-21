
#pragma once

#ifndef KIWI_CORE_TYPEID
#define KIWI_CORE_TYPEID

#include "kiwi/core/Commons.hpp"

namespace kiwi{
namespace core{

typedef size_t TypeID;


template< typename T >
struct TypeIndexGenerator
{
private: TypeIndexGenerator(){}
public:
	static TypeID Get()
	{
        static char addressOfThisIsTheTypeId;
		return reinterpret_cast< TypeID >( &addressOfThisIsTheTypeId );
	}
};

// qualifier stripping
template< typename T >
struct TypeIndexGenerator< const T >
{
private: TypeIndexGenerator(){}
public:
    static TypeID Get()
	{
        return TypeIndexGenerator<T>::Get();
	}
};
template< typename T >
struct TypeIndexGenerator< volatile T >
{
private: TypeIndexGenerator(){}
public:
    static TypeID Get()
	{
        return TypeIndexGenerator<T>::Get();
	}
};

// -----------------------------------------------------------------------------

template <typename T> TypeID TypeOf(const T&)
{
    return TypeIndexGenerator<T>::Get();
}

template <typename T> TypeID TypeOf()
{
    return TypeIndexGenerator<T>::Get();
}

template <typename T> TypeID TypeIndexOf(const T&)
{
    return TypeIndexGenerator<T>::Get();
}

template <typename T> TypeID TypeIndexOf()
{
    return TypeIndexGenerator<T>::Get();
}



}//namespace
}//namespace

#endif 
