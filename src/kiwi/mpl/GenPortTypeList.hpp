
// Not working yet. This tool is not a priority, it would just provide a nicer syntaxe
// for layout declaration

#ifndef KIWI_MPL_GENPORTTYPELIST_HPP
#define KIWI_MPL_GENPORTTYPELIST_HPP

#include "kiwi/core/StaticPorts.hpp"

namespace kiwi{
namespace mpl{

template<class TypeList_t, class Policy_t> 
struct genReaderPortTypeList{
  typedef
    TypeList<kiwi::core::StaticReaderPort<typename TypeList_t::type,Policy_t>
      , typename genReaderPortTypeList<typename TypeList_t::tail,Policy_t>::type >
        type;
};

template<class Policy_t>
struct genReaderPortTypeList<EmptyTypeList, Policy_t>{
  typedef EmptyTypeList type;
};


}//namespace
}//namespace

#endif
