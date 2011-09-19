#ifndef KIWI_MPL_INFINITETYPELIST_HPP
#define KIWI_MPL_INFINITETYPELIST_HPP


namespace kiwi{
namespace mpl{

/**
 * A fake typelist that contains teh same type with an infinite size.
 */ 
template<typename T>
struct InfiniteTypeList{
  enum { size = -1 };
  typedef T type;
  typedef InfiniteTypeList<T> tail;
};


}//namespace
}//namespace


#endif
