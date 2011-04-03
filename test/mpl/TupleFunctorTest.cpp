
#include "kiwi/mpl/TypeList.hpp"
#include "kiwi/mpl/TupleApplyFunctor.hpp"
#include <assert.h>


using namespace kiwi;
using namespace kiwi::mpl;

typedef TypeList_3(int,float,char) list_ifc;

struct myFunctor{
  template<typename T> void operator()(T& var){ var += _n; }
  myFunctor(int n) : _n(n){}
  int _n;
};

int main()
{
  ScopedBlockMacro("TupleFunctor::Test")

  Tuple<list_ifc> aTuple;
  myFunctor func(1);

  tuple::at<0>::get(aTuple) = 42;
  tuple::at<1>::get(aTuple) = 3.1415;
  tuple::at<2>::get(aTuple) = 12;
  
  tuple::ApplyFunctor< Tuple<list_ifc> >::exec(aTuple,func);

  Debug::print() << tuple::at<1>::get(aTuple) <<"\n";
  assert( tuple::at<0>::get(aTuple) == 43);
  assert( tuple::at<1>::get(aTuple) == 4.1415f );
  assert( tuple::at<2>::get(aTuple) == 13);

}
