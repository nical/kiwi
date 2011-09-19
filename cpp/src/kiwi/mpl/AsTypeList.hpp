
#ifndef KIWI_MPL_ASTYPELIST
#define KIWI_MPL_ASTYPELIST

#include "kiwi/mpl/TypeList.hpp"


namespace kiwi{
namespace mpl{


template<typename T> struct AsTypeList{
  typedef TypeList_1(T) type;
};
template<typename T1,typename T2> struct AsTypeList< TypeList<T1,T2> >{
  typedef TypeList<T1,T2> type;
};


}//namespace
}//namespace


#endif
