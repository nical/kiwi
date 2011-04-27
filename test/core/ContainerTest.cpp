
#include "kiwi/core/Container.hpp"
#include <assert.h>

using kiwi::out;
using kiwi::endl;

int main(){
  ScopedBlockMacro("core::Container::Test")
  

  IntContainer ic;
  Vector3iContainer vect3i(42,1337,12);

  out.beginBlock("subContainer tests");
  kiwi_assert( vect3i.subContainer<0>().value() == 42  );
  kiwi_assert( vect3i.subContainer<1>().value() == 1337);
  kiwi_assert( vect3i.subContainer<2>().value() == 12  );
  Vector3iContainer::subContainerInfo<0>::type& subc0 = vect3i.subContainer<0>();
  out.endBlock("subContainer tests");

}
