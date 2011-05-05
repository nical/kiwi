
#include "kiwi/core/Container.hpp"
#include <assert.h>

using kiwi::out;
using kiwi::endl;

int main(){
  KIWI_BEGIN_TESTING("core::Container")
  

  IntContainer ic;
  Vector3iContainer vect3i(42,1337,12);

  KIWI_TEST( "Checking the first subcontainer.","core.c.01"
    vect3i.subContainer<0>().value() == 42  );
  KIWI_TEST( "Checking the second subcontainer.","core.c.02"
    vect3i.subContainer<1>().value() == 1337);
  KIWI_TEST( "Checking the third subcontainer.","core.c.03"
    vect3i.subContainer<2>().value() == 12  );
    
  Vector3iContainer::subContainerInfo<0>::type& subc0 = vect3i.subContainer<0>();
  
  return KIWI_END_TESTING
}
