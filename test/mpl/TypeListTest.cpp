
#include "kiwi/mpl/TypeList.hpp"
#include <assert.h>

typedef TypeList_10(int,float,char,int,double,bool,float,unsigned int,short,char) list1;
typedef TypeList_5(float,int,double,bool,char) list2;


int main(){
  ScopedBlockMacro("TypeList::Test")

  assert( list1::size == 10 );
  assert( list2::size == 5 );
  
  return 0;
}
