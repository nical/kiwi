
#include "kiwi/utils/Testing.hpp"
#include "kiwi/mpl/FillTypeList.hpp"
#include "kiwi/mpl/SameType.hpp"

using kiwi::out;
using kiwi::endl;

using namespace kiwi::mpl;

int main(){
  KIWI_BEGIN_TESTING("mpl::FillTypeList")

  typedef TypeList_3(int,char,float ) icf;
  typedef TypeList_4(int,int,int,int) iiii;
  typedef TypeList_6(bool,bool,bool,int,char,float) icfbbb;
  typedef FillTypeList<bool,6,icf>::type icf__b;
  typedef FillTypeList<int,4>::type fill___i;

  bool test1 = SameType<icfbbb,icf__b>::value;
  bool test2 = SameType<iiii,fill___i>::value;

  KIWI_TEST("Appending types at the begining of a TypeList.","mpl.ft.01", test1 )
  KIWI_TEST("filling an empty TypeList.","mpl.ft.02", test2 )
  
  return KIWI_END_TESTING
}
