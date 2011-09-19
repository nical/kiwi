#ifndef KIWI_MPL_APPLYBITMASK_HPP
#define KIWI_MPL_APPLYBITMASK_HPP

#include "kiwi/mpl/Number.hpp"

namespace kiwi{
namespace mpl{

template<typename num1, typename num2> struct ApplyAndOperator{
  enum{ value = num1::value & num2::value };
  typedef Number<value> type;
};

template<typename num1, typename num2> struct ApplyOrOperator{
  enum{ value = num1::value | num2::value };
  typedef Number<value> type;
};

template<typename num1> struct ApplyNotOperator{
  enum{ value = !num1::value };
  typedef Number<value> type;
};

}//namespace
}//namespace

#endif
