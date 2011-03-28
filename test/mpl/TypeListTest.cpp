
#include "kiwi/mpl/TypeList.hpp"
#include <assert.h>

typedef TypeList_10(int,float,char,int,double,bool,float,unsigned int,short,char) list1;


int main(){
  ScopedBlockMacro("TypeList::Test")

  assert( list1::size ==10 );
  
  return 0;
}
