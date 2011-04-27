
#include "kiwi/utils/DebugStream.hpp"
#include "kiwi/mpl/MakeContainer.hpp"
#include "kiwi/mpl/SameType.hpp"
#include <assert.h>

using kiwi::out;
using kiwi::endl;

int main(){
  ScopedBlockMacro("mpl::MakeContainer::Test")

  typedef kiwi::mpl::MakeContainer<int>::type makecontainer_int;
  typedef kiwi::mpl::MakeContainer< kiwi::core::ContainerWrapper<int> >::type makecontainer_cw_int;
  typedef kiwi::core::ContainerWrapper<int> containerwrapper_int;
  bool makecontainer_test1
    = kiwi::mpl::SameType<containerwrapper_int,makecontainer_int>::value;
  bool makecontainer_test2
    = kiwi::mpl::SameType<containerwrapper_int,makecontainer_cw_int>::value;

  assert( kiwi::mpl::MakeContainer<int>::introduceChange );
  assert( !kiwi::mpl::MakeContainer< kiwi::core::ContainerWrapper<int> >::introduceChange );
    
  assert( makecontainer_test1 );
  assert( makecontainer_test2 );

  

}
