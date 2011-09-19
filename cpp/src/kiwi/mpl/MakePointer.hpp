
#ifndef KIWI_MPL_MAKEPOINTER_HPP
#define KIWI_MPL_MAKEPOINTER_HPP

namespace kiwi{
namespace mpl{

template<typename T> struct MakePointer{
  typedef T* type;
};

template<typename T> struct MakePointer_2{
  typedef T** type;
};

}//namespace
}//namespace

#endif
