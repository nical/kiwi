
#ifndef KIWI_MPL_MAKE_CONTAINER
#define KIWI_MPL_MAKE_CONTAINER

#include "kiwi/core/Container.hpp"
#include "kiwi/mpl/IsRelated.hpp"

namespace kiwi{
namespace mpl{

//forward declaration
template<int isrelated, typename T> struct MakeContainer_;

/**
 * [Type generator] Creates a ContainerWrapper of T if T is not already a container.
 *
 * In the case T is a container (i.e. a direct or indirect child of
 * kiwi::core::AbstractContainer) the resulting type is T unchanged.
 *
 */ 
template<typename T> struct MakeContainer{
  typedef typename
    MakeContainer_<(int)IsRelated<core::AbstractContainer,T>::value,T>::type type;
  enum{ introduceChange
    = MakeContainer_<(int)IsRelated<core::AbstractContainer,T>::value,T>::introduceChange};
};


template<int isrelated, typename T> struct MakeContainer_{
  typedef T type;
  enum{ introduceChange = 0 };
};
template<typename T> struct MakeContainer_<0,T>{
  typedef core::ContainerWrapper<T> type;
  enum{ introduceChange = 1 };
};


}//namespace
}//namespace


#endif
