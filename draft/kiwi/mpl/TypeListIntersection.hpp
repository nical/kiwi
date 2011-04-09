
#ifndef KIWI_MPL_TYPELISTINTERSECTION_HPP
#define KIWI_MPL_TYPELISTINTERSECTION_HPP

#include "kiwi/mpl/SameType.hpp"

namespace kiwi{
namespace mpl{
namespace typelist{

template<typename T1, typename T2>
struct _intersection2{
  enum{
    value = (SameType<typename T1::type,typename T2::type>::value || _intersection2<typename T1::tail,T2>::value)
  };
};

template<typename T1, typename T2>
struct _intersection1{
  enum{
    value = (SameType<typename T1::type,typename T2::type>::value || _intersection2<T1,typename T2::tail>::value)
  };
};

template<typename T1> struct _intersection1<T1,EmptyTypeList>{enum{ value = 0 };};
template<typename T2> struct _intersection2<EmptyTypeList,T2>{enum{ value = 0 };};

template<typename T1, typename T2>
struct intersection{
  enum{ value = _intersection1<T1,T2>::value };

};


}//namespace
}//namespace
}//namespace

#endif
