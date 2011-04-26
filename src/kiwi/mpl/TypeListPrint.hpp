
#ifndef KIWI_MPL_TYPELISTPRINT_HPP
#define KIWI_MPL_TYPELISTPRINT_HPP

#include "kiwi/mpl/TypeToStr.hpp"

namespace kiwi{
namespace mpl{
namespace typelist{



template<typename typelist_> struct print_{
  template<typename StreamType> static void in(StreamType& stream){
    stream << TypeToStr<typename typelist_::type>::str() << ", ";
    print_<typename typelist_::tail>::in(stream);
  }
}; 



template<> struct print_<EmptyTypeList>{
  template<typename StreamType> static void in(StreamType& stream){
    stream << "EmptyTypeList";
  }
};



template<typename typelist_> struct print{
  template<typename StreamType> static void in(StreamType& stream){
    stream << "TypeList< ";
    print_<typename typelist_::tail>::in(stream);
    stream << " >";
  }
}; 



}//namespace
}//namespace
}//namespace

#endif
