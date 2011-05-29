
#ifndef KIWI_MPL_TYPELISTTRANSFORM_HPP
#define KIWI_MPL_TYPELISTTRANSFORM_HPP

#include "kiwi/mpl/TypeList.hpp"

namespace kiwi{
namespace mpl{
namespace typelist{


template<typename typelist_, template<typename T> class transformation >
struct Transform{
  typedef TypeList<
      typename transformation<typename typelist_::type>::type
    , typename Transform<typename typelist_::tail,transformation>::type
  > type;
};

template<template<typename T> class transformation >
struct Transform<EmptyTypeList,transformation>{
  typedef EmptyTypeList type;
};




}//namespace
}//namespace
}//namespace




#endif
