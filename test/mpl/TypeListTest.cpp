
#include "kiwi/mpl/TypeList.hpp"
#include "kiwi/mpl/SameType.hpp"
#include "kiwi/mpl/GenPortTypeList.hpp"
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


  
  return 0;
}
