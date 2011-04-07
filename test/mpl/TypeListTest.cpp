
#include "kiwi/mpl/TypeList.hpp"
#include "kiwi/mpl/SameType.hpp"
#include "kiwi/mpl/GenPortTypeList.hpp"
#include "kiwi/mpl/TypeListIntersection.hpp"
#include "kiwi/mpl/TypeListHas.hpp"
#include <assert.h>

class A : public kiwi::core::Container{};
class B : public kiwi::core::Container{};


typedef TypeList_10(int,float,char,int,double,bool,float,unsigned int,short,char) list1;
typedef TypeList_5(float,int,double,bool,char) list2;
typedef TypeList_2(A,B) listContainers;
typedef kiwi::core::StaticReaderPort<A,kiwi::core::AlwaysCompatibleConnectionPolicy> SRPA;
typedef kiwi::core::StaticReaderPort<B,kiwi::core::AlwaysCompatibleConnectionPolicy> SRPB;

int main(){
  ScopedBlockMacro("TypeList::Test")

  assert( list1::size == 10 );
  assert( list2::size == 5 );

  int test =  kiwi::mpl::typelist::intersection<TypeList_2(int,float),TypeList_2(char,float)>::value;
  int test2 =  kiwi::mpl::typelist::intersection<TypeList_2(int,float),TypeList_2(char,short)>::value;
  int test3 = kiwi::mpl::typelist::has<TypeList_3(int,float,char),float>::value;
  int test4 = kiwi::mpl::typelist::has<TypeList_3(int,float,char),short>::value;
  assert(test);
  assert(!test2);
  assert(test3);
  assert(!test4);
  
  return 0;
}
