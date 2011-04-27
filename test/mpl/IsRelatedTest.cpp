
#include "kiwi/utils/DebugStream.hpp"
#include "kiwi/mpl/IsRelated.hpp"

#include <assert.h>

using kiwi::out;
using kiwi::endl;

class A{};
class A1 : public A {};
class A11 : public A1 {};
class B{};

int main(){
  ScopedBlockMacro("mpl::IsRelated::Test")

  
  
  int isrelatedtest_n1  = kiwi::mpl::IsRelated<A,int>::value;
  int isrelatedtest_n2  = kiwi::mpl::IsRelated<A,B>::value;
  int isrelatedtest_n3  = kiwi::mpl::IsRelated<A11,A>::value;
  int isrelatedtest1 = kiwi::mpl::IsRelated<int,float>::value;
  int isrelatedtest2 = kiwi::mpl::IsRelated<A,A11>::value;
  int isrelatedtest3 = kiwi::mpl::IsRelated<A1,A1>::value;
   
  assert(!isrelatedtest_n1);
  assert(!isrelatedtest_n2);
  assert(!isrelatedtest_n3);
  assert(isrelatedtest1);
  assert(isrelatedtest2);
  assert(isrelatedtest3);

  
  out << "isRelated constants: "
    << (int) kiwi::mpl::IsRelated<B, int>::value
    << " " << (int) kiwi::mpl::IsRelated<int,float>::value << endl;
  

}
