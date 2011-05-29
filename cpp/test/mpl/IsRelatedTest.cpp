
#include "kiwi/utils/DebugStream.hpp"
#include "kiwi/mpl/IsRelated.hpp"
#include "kiwi/utils/Testing.hpp"

#include <assert.h>

using kiwi::out;
using kiwi::endl;

class A{};
class A1 : public A {};
class A11 : public A1 {};
class B{};

int main(int argc, char** argv){
  KIWI_BEGIN_TESTING("mpl::IsRelated")
  out.parseArgs(argc,argv);
  
  // A & int are not related
  int isrelatedtest_n1  = kiwi::mpl::IsRelated<A,int>::value; //false
  // A & B are not related
  int isrelatedtest_n2  = kiwi::mpl::IsRelated<A,B>::value;   //false
  // wrong argument order cannot convert mother class into child class 
  int isrelatedtest_n3  = kiwi::mpl::IsRelated<A11,A>::value; //false
  // A float can be converted into an int 
  int isrelatedtest1 = kiwi::mpl::IsRelated<int,float>::value;//true
  // A11 is within A's hierarchy
  int isrelatedtest2 = kiwi::mpl::IsRelated<A,A11>::value;    //true
  // class "are related" to themselves
  int isrelatedtest3 = kiwi::mpl::IsRelated<A1,A1>::value;    //true
   
  KIWI_TEST( "A and int should not be related.","mpl.ir.01",
    !isrelatedtest_n1 );
  KIWI_TEST( "A and B should not be related.","mpl.ir.02",
    !isrelatedtest_n2 );
  KIWI_TEST( "A and int should not be related.","mpl.ir.03",
    !isrelatedtest_n3 );
  KIWI_TEST( "A float can be converted into an int (thus they're related).","mpl.ir.04",
    isrelatedtest1 );
  KIWI_TEST( "A11 is within A's hierachy.","mpl.ir.05",
    isrelatedtest2);
  KIWI_TEST( "Any class is 'related' to itself.","mpl.ir.06",
    isrelatedtest3);

  return KIWI_END_TESTING;
}
