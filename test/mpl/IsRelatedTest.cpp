
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

  
  // A & int are not related
  int isrelatedtest_n1  = kiwi::mpl::IsRelated<A,int>::value; //false
  // A & B are not related
  int isrelatedtest_n2  = kiwi::mpl::IsRelated<A,B>::value;   //false
  // wrong argument order cannot convert mother class into child class 
  int isrelatedtest_n3  = kiwi::mpl::IsRelated<A11,A>::value; //false
  // a float can be converted into an int 
  int isrelatedtest1 = kiwi::mpl::IsRelated<int,float>::value;//true
  // A11 is within A's hierarchy
  int isrelatedtest2 = kiwi::mpl::IsRelated<A,A11>::value;    //true
  // class "are related" to themselves
  int isrelatedtest3 = kiwi::mpl::IsRelated<A1,A1>::value;    //true
   
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
