#ifndef KIWI_MPL_NUMBER_HPP
#define KIWI_MPL_NUMBER_HPP

#include "kiwi/core/Commons.hpp"

namespace kiwi{
namespace mpl{

/**
 * Simple struct that wraps integral numbers into types so that they can be passed
 * as template parameters of certain mpl algorithms
 */ 
template<int N> struct Number{
  enum { value = N };
  typedef Number<N+1> Next;
  typedef Number<N-1> Previous;
};

template<typename T> struct IsMPLNumber{
  enum{ value = 0 };
  typedef false_t type; 
};
template<int N> struct IsMPLNumber<Number<N> >{
  enum{ value = 1 };
  typedef true_t type; 
};

}//namespace
}//namespace


#endif
