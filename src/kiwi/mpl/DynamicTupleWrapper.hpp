#ifndef KIWI_MPL_DYNAMICTUPLEWRAPER_HPP
#define KIWI_MPL_DYNAMICTUPLEWRAPER_HPP


namespace kiwi{
namespace mpl{

namespace internals{
template<typename Tuple_t, typename HighLevelType, int i>
struct IndexedWrapper{
  static void exec(Tuple_t& tuple, HighLevelType** array){
    array[i] = &tuple._obj;
    IndexedWrapper<typename Tuple_t::NestedTuple, HighLevelType, i+1>
      ::exec(tuple._next, array);
  }
};

template<typename HighLevelType, int i>
struct IndexedWrapper<EmptyTuple,HighLevelType, i>{
  static void exec(EmptyTuple& tuple, HighLevelType** array){};
};
}//namespace internals


struct DynamicTupleWrapper{
  template<typename Tuple_t, typename HighLevelType>
  static void exec(Tuple_t& tuple, HighLevelType** array){
    internals::IndexedWrapper<Tuple_t,HighLevelType,0>
      ::exec(tuple,array);
  }
};

}//namespace
}//namespace

#endif
