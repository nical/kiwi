#ifndef KIWI_MPL_FILLTYPELIST_HPP
#define KIWI_MPL_FILLTYPELIST_HPP

#include "kiwi/mpl/TypeList.hpp"

namespace kiwi{
namespace mpl{



template<typename T, int sizeDiff_, typename typelist_> 
struct FillTypeList_{
  enum{ sizeDiff = sizeDiff_ - 1 };
  typedef typename FillTypeList_<T,sizeDiff,kiwi::mpl::TypeList<T,typelist_> >::type type;
};

template<typename T, typename typelist_> 
struct FillTypeList_<T,0,typelist_>{
  typedef typelist_ type;
};




template<typename T, int size, typename typelist_ = EmptyTypeList> 
struct FillTypeList{
  typedef typename FillTypeList_<T, size - typelist_::size, typelist_>::type type;
};


}//namespace
}//namespace


#endif
