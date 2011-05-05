#include "kiwi/utils/Testing.hpp"
#include "kiwi/utils/DebugStream.hpp"
#include "kiwi/mpl/MakeContainer.hpp"
#include "kiwi/mpl/SameType.hpp"
#include <assert.h>

using kiwi::out;
using kiwi::endl;

int main(){
  KIWI_BEGIN_TESTING("mpl::MakeContainer")

  // preparing some of the tests
  typedef kiwi::mpl::MakeContainer<int>::type makecontainer_int;
  typedef kiwi::mpl::MakeContainer< kiwi::core::ContainerWrapper<int> >::type makecontainer_cw_int;
  typedef kiwi::core::ContainerWrapper<int> containerwrapper_int;
  bool makecontainer_test1
    = kiwi::mpl::SameType<containerwrapper_int,makecontainer_int>::value;
  bool makecontainer_test2
    = kiwi::mpl::SameType<containerwrapper_int,makecontainer_cw_int>::value;
  
  // the tests 
  KIWI_TEST( "MakeContainer has to wrap int into a container class (introduces a change)","mpl.mc.01",
    kiwi::mpl::MakeContainer<int>::introduceChange );

  KIWI_TEST( "ContainerWrapper<int> already a container (introduces no change)","mpl.mc.02",
   !kiwi::mpl::MakeContainer< kiwi::core::ContainerWrapper<int> >::introduceChange );
    
  KIWI_TEST( "MakeContainer<int> should generate ContainerWrapper<int>","mpl.mc.03",
    makecontainer_test1 );

  KIWI_TEST( "MakeContainer<ContainerWrapper<int> > should generate ContainerWrapper<int>","mpl.mc.04",
    makecontainer_test2 );

  return KIWI_END_TESTING
}
