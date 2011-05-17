
#include "kiwi/utils/DebugStream.hpp"
#include "kiwi/utils/Testing.hpp"
#include "kiwi/core/Container.hpp"
#include <assert.h>

using kiwi::out;
using kiwi::endl;

class foo{
  public: template<int N> struct bar{ enum{ value = -1 }; };
  int nbSubContainers() { return 3; }
  inline int subContainer(int index);
};

template<> struct foo::bar<0>{ enum{ value = 0 }; };
template<> struct foo::bar<1>{ enum{ value = 1 }; };
template<> struct foo::bar<2>{ enum{ value = 2 }; };

int foo::subContainer(int index) {
    switch(index){
      case 0: return bar<0>::value;
      case 1: return bar<1>::value;
      case 3: return bar<3>::value;
      default : return 0;
    }
  }

int main(){
  KIWI_BEGIN_TESTING("core::Container")
  
  /*
  IntContainer ic;
  Vector3iContainer vect3i(42,1337,12);

  KIWI_TEST( "Checking the first subcontainer.","core.c.01",
    vect3i.subContainer<0>().value() == 42  );
  KIWI_TEST( "Checking the second subcontainer.","core.c.02",
    vect3i.subContainer<1>().value() == 1337);
  KIWI_TEST( "Checking the third subcontainer.","core.c.03",
    vect3i.subContainer<2>().value() == 12  );
    
  Vector3iContainer::subContainerInfo<0>::type& subc0 = vect3i.subContainer<0>();
  */

  out << (int)foo::bar<0>::value
      << " " << (int)foo::bar<1>::value
      << " " << (int)foo::bar<2>::value
      << " " << (int)foo::bar<3>::value
  << endl;
  return KIWI_END_TESTING
}
