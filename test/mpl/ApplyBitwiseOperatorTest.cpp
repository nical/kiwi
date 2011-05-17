
#include "kiwi/mpl/ApplyBitwiseOperator.hpp"
#include "kiwi/mpl/SameType.hpp"
#include "kiwi/utils/Testing.hpp"

using kiwi::out;
using kiwi::endl;

using namespace kiwi::mpl;

int main(){
  KIWI_BEGIN_TESTING("mpl::ApplyBitwiseOperator")

  int andTest1 = ApplyAndOperator< Number<7>, Number<4> >::value; // 111 & 001
  int andTest2 = ApplyAndOperator< Number<42>, Number<42> >::value; // 010101
  int andTest3 = ApplyOrOperator< Number<2>, Number<7> >::value; // 010 | 111
  int andTest4 = ApplyOrOperator< Number<2>, Number<4> >::value; // 010 | 111
  KIWI_TEST("ApplyAndOperator: 111 & 001", "mpl.op.01", andTest1 == 4 )
  KIWI_TEST("ApplyAndOperator: X & X", "mpl.op.02", andTest2 == 42 )
  KIWI_TEST("ApplyOrOperator: 010 | 111", "mpl.op.03", andTest3 == 7 )
  KIWI_TEST("ApplyOrOperator: 010 | 001", "mpl.op.06", andTest4 == 6 )

  
  return KIWI_END_TESTING
}
