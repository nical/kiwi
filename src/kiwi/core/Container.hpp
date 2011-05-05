
#ifndef KIWI_CORE_CONTAINER_HPP
#define KIWI_CORE_CONTAINER_HPP

#include "kiwi/mpl/TypeList.hpp"
#include "kiwi/mpl/Tuple.hpp"

namespace kiwi{
namespace core{


/**
 * Abstract mother class for containers.
 *
 * Having this class allows to use kiwi::mpl::IsRelated with containers that is
 * needed by the implementation of kiwi::mpl::MakeContainer. 
 */ 
class AbstractContainer{ public: virtual ~AbstractContainer(){} };

/**
 * The class that implements the composite container's mecanism.
 *
 * Custom containers should inherit this class;
 */ 
template<typename TSubContainers>
class CompositeContainer : public AbstractContainer{
public:
  typedef TSubContainers SubContainersTypeList;
  enum { NbSubContainers = SubContainersTypeList::size };
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

template<typename TValueType>
struct ContainerWrapper : public Container{
  typedef TValueType ValueType;
  enum { NbSubContainers = 0 };
  typedef mpl::EmptyTypeList SubContainersTypeList;
  
  ValueType data;
};


}//namespace
}//namespace


#endif
