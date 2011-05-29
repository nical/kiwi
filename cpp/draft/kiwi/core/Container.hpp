
#ifndef KIWI_CORE_CONTAINER_HPP
#define KIWI_CORE_CONTAINER_HPP

#include "kiwi/mpl/TypeList.hpp"
#include "kiwi/mpl/Tuple.hpp"

namespace kiwi{
namespace core{

template<typename TSubContainers>
class CompositeContainer{
public:
  typedef TSubContainers SubContainersTypeList;
  template<int i>
  struct subContainerInfo{
    typedef typename kiwi::mpl::typelist::at<SubContainersTypeList,i>::type type;
  };
  template<int i>
  typename kiwi::mpl::typelist::at<SubContainersTypeList,i>::type&
  subContainer(){
    return kiwi::mpl::tuple::at<i>::get(_subContainers);
  }
  
protected:
  typedef kiwi::mpl::Tuple<TSubContainers> SubContainerTuple;
  SubContainerTuple _subContainers;
};

typedef CompositeContainer<kiwi::mpl::EmptyTypeList> Container;

}//namespace
}//namespace


#endif
