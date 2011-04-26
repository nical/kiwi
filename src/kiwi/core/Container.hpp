
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

template<typename TValueType>
struct ContainerWrapper : public Container{
  typedef TValueType ValueType;
  ValueType data;
};

// ---------------------------------------------------------------- Is container
template<typename T>
struct IsContainer{
  typedef false_t type;
  static const int value = 0;
};
template<typename T>
struct IsContainer< CompositeContainer<T> >{
  typedef true_t type;
  static const int value = 1;
};

// -------------------------------------------------------------- make Container

}//namespace
}//namespace


#endif
