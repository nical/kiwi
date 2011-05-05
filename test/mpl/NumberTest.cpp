
#include "kiwi/mpl/Number.hpp"
#include "kiwi/mpl/SameType.hpp"
#include "kiwi/utils/Testing.hpp"

using kiwi::out;
using kiwi::endl;

int main(){
  KIWI_BEGIN_TESTING("mpl::Number")

  typedef kiwi::mpl::Number<1> _1;
  typedef kiwi::mpl::Number<2> _2;
  typedef kiwi::mpl::Number<3> _3;
  typedef kiwi::mpl::Number<-1> _m1;

  
  int test4 = kiwi::mpl::SameType<_m1::Next::Next::Next::Next,_3>::value;
  

  KIWI_TEST("Nulber<1>::value == 1","mpl.nb.01", _1::value == 1 )
  KIWI_TEST("Nulber<-1>::value == -1","mpl.nb.02", _m1::value == -1 )
  KIWI_TEST("Nulber<1>::value + Nulber<-1>::value == 0","mpl.nb.03"
    , _1::value + _m1::value == 0 )

  KIWI_TEST("Nulber<N>::Next", "mpl.nb.04", test4 )
  KIWI_TEST("Nulber<N>::Previous", "mpl.nb.05", _2::Next::Previous::value == _2::value )
  KIWI_TEST("IsMPLNumber", "mpl.nb.06", kiwi::mpl::IsMPLNumber<_1>::value )
  KIWI_TEST("(not)IsMPLNumber", "mpl.nb.07", !kiwi::mpl::IsMPLNumber<float>::value )
  
  return KIWI_END_TESTING
}
