
#ifndef KIWI_MPL_TYPELISTHAS_HPP
#define KIWI_MPL_TYPELISTHAS_HPP


namespace kiwi{
namespace mpl{
namespace typelist{

template<typename _typelist, typename T>
struct has{
  enum{
    value = SameType<T,typename _typelist::type>::value || has<typename _typelist::tail, T>::value
  };
};

template<typename T> struct has<EmptyTypeList, T>{ enum{ value = 0 }; };


}//namespace
}//namespace
}//namespace


#endif
