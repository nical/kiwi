
#include "kiwi/utils/Testing.hpp"
#include "kiwi/mpl/TypeListTransform2.hpp"
#include "kiwi/mpl/SameType.hpp"

using kiwi::out;
using kiwi::endl;



template<typename T1,typename T2>
struct static_pair{
  typedef T1 type1;
  typedef T2 type2;
  typedef static_pair<T1,T2> type;

  T1 first;
  T2 second;
};


int main(){
  KIWI_BEGIN_TESTING("mpl::TypeListTransform2")

  typedef kiwi::mpl::typelist::Transform2<TypeList_3(int,float,char),TypeList_3(double,short,bool), static_pair>::type transformed;

  typedef kiwi::mpl::typelist::Transform2<TypeList_5(int,float,char,int,short),TypeList_3(double,short,bool), static_pair>::type transformed2;

  typedef kiwi::mpl::typelist::Transform2<TypeList_3(int,float,char),TypeList_4(double,short,bool,float), static_pair>::type transformed3;

  
  typedef static_pair<int,double> p1;
  typedef static_pair<float,short> p2;
  typedef static_pair<char,bool> p3;
  
  int test01 = kiwi::mpl::SameType< TypeList_3(p1,p2,p3), transformed>::value;
  int test02 = kiwi::mpl::SameType< TypeList_3(p1,p2,p3), transformed2>::value;
  int test03 = kiwi::mpl::SameType< TypeList_3(p1,p2,p3), transformed3>::value;

  KIWI_TEST("check kiwi::mpl::Transform2 on a pair of small lists.","mpl.t2.01",test01)
  KIWI_TEST("With the first list longer than the second.","mpl.t2.02",test02)
  KIWI_TEST("With the second list longer than the first.","mpl.t2.03",test03)
  
  return KIWI_END_TESTING
}

