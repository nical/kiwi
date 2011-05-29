
#ifndef KIWI_MPL_TUPLEFUNCTOR_HPP
#define KIWI_MPL_TUPLEFUNCTOR_HPP

#include "kiwi/mpl/Tuple.hpp"

namespace kiwi{
namespace mpl{
namespace tuple{



template<typename tuple_>
struct ApplyFunctor{
  template<typename functor>
  static void exec(tuple_& tuple, functor& func){
    func( tuple._obj );
    ApplyFunctor<typename tuple_::NestedTuple>::exec(tuple._next,func);
  }

};

template<>
struct ApplyFunctor<EmptyTuple>{
  template<typename functor>
  static void exec(EmptyTuple& tuple, functor& func){}
};


}//namespace
}//namespace
}//namespace


#endif
