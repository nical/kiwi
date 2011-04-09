
#include <assert.h>
#include "kiwi/core/Container.hpp"
#include "kiwi/core/DummyContainer.hpp"
#include "kiwi/utils/DebugStream.hpp"

using kiwi::out;
using kiwi::endl;

int main(){
  out.beginBlock("kiwi v2::test");
  out << "kiwi v2::test" << endl;

  IntContainer ic;
  Vector3iContainer vect3i(42,1337,12);

  assert( *vect3i.subContainer<0>().value == 42 );
  assert( *vect3i.subContainer<1>().value == 1337 );
  assert( *vect3i.subContainer<2>().value == 12 );

  out.indentation++;
  out << "indent" << " test" << endl << "foo" << endl;
  out.indentation++;
  out << "indent test" << endl << "foo" << endl;
  out.indentation-=2;
  out << "end of the test" << endl;
  

  

}
