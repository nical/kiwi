
#ifndef KIWI_MPL_TYPETOSTR_HPP
#define KIWI_MPL_TYPETOSTR_HPP

#include <typeinfo>
#include "kiwi/core/Commons.hpp"
#define KIWI_TYPETOSTR_OVERLOAD( type_name ) template<> struct TypeToStr<kiwi::type_name>{ static const kiwi::string str(){ return #type_name; } };
#define KIWI_TYPETOSTR_OVERLOAD_2( type_name ) template<> struct TypeToStr<type_name>{ static const kiwi::string str(){ return #type_name; } };

namespace kiwi{
namespace mpl{

template<typename T> struct TypeToStr{
  static const kiwi::string str(){ return typeid(T).name(); }
};

KIWI_TYPETOSTR_OVERLOAD(int8)
KIWI_TYPETOSTR_OVERLOAD(uint8)
KIWI_TYPETOSTR_OVERLOAD(int16)
KIWI_TYPETOSTR_OVERLOAD(uint16)
KIWI_TYPETOSTR_OVERLOAD(int32)
KIWI_TYPETOSTR_OVERLOAD(uint32)
KIWI_TYPETOSTR_OVERLOAD(NullType)

KIWI_TYPETOSTR_OVERLOAD_2(float)
KIWI_TYPETOSTR_OVERLOAD_2(double)

template<typename T> struct TypeToStr<T*>{
  static const kiwi::string str(){ return TypeToStr<T>::str()+"*"; }
};


template<typename T> struct type{
  static const kiwi::string str() { return TypeToStr<T>::str(); }
};

}//namespace
}//namespace

#endif
