
#ifndef KIWI_MPL_TYPELISTTRANSFORM2_HPP
#define KIWI_MPL_TYPELISTTRANSFORM2_HPP

#include "kiwi/mpl/TypeList.hpp"

namespace kiwi{
namespace mpl{
namespace typelist{


template<typename typelist1_, typename typelist2_, template<typename T1,typename  T2> class transformation >
struct Transform2{
  typedef TypeList<
      typename transformation<typename typelist1_::type,typename typelist2_::type>::type
    , typename Transform2<typename typelist1_::tail,typename typelist2_::tail,transformation>::type
  > type;
};


template<template<typename T1,typename T2> class transformation, typename typelist2_ >
struct Transform2<EmptyTypeList,typelist2_,transformation>{
  typedef EmptyTypeList type;
};
template<template<typename T1,typename T2> class transformation, typename typelist1_ >
struct Transform2<typelist1_,EmptyTypeList,transformation>{
  typedef EmptyTypeList type;
};
template<template<typename T1,typename T2> class transformation>
struct Transform2<EmptyTypeList,EmptyTypeList,transformation>{
  typedef EmptyTypeList type;
};




}//namespace
}//namespace
}//namespace




#endif

