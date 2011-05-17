#pragma once
#ifndef KIWI_CORE_STATICDATAPORT_DECL_HPP
#define KIWI_CORE_STATICDATAPORT_DECL_HPP

#include "AbstractDataPort.hpp"
#include "Container.hpp"
#include "kiwi/mpl/FillTypeList.hpp"
#include "kiwi/mpl/Number.hpp"
#include "kiwi/mpl/MakeContainer.hpp"
#include "kiwi/mpl/TypeListTransform2.hpp"

namespace kiwi{
namespace core{

// forward declaration



/// transforms T into const T if Flag is READ
template<typename T, AccessFlag Flag> struct ApplyConstModifier{
  typedef T type;
};
template<typename T> struct ApplyConstModifier<T, READ>{
  typedef const T type;
};

template<typename container, typename flag> struct _MakeStaticDataPort;

/**
 * DataPort templated implementation.
 *
 * Template parameters:
 *  - the container type (automatically wrapped into a container if necessary)
 *  - the AccessFlag (READ, WRITE, READ_WRITE ...)
 *  - [opt] a list of access flags for the subContainers. The list is generated
 *      automatically using this port's AccessFlag by default.
 */
template<typename TContainerType, AccessFlag TAccessFlag>
class StaticDataPort : public AbstractDataPort
{
public:
  static const AccessFlag Flag = TAccessFlag;
  typedef typename mpl::MakeContainer<TContainerType>::type ContainerType;

  typedef typename mpl::FillTypeList<
        mpl::Number<TAccessFlag>,
        mpl::MakeContainer<TContainerType>::type::NbSubContainers
      >::type SubAccessFlagsList;
  
  typedef typename mpl::typelist::Transform2<
    typename ContainerType::SubContainersTypeList
    ,SubAccessFlagsList, _MakeStaticDataPort>::type SubPortsTypList;
  
  AccessFlag flag() const { return Flag; }

  typename ApplyConstModifier<ContainerType,Flag>::type * container() {
    return _container;
  }
  Container* abstractContainer() { return _container; }
  
protected:  
  ContainerType* _container;
};





template<typename container, typename flag> struct _MakeStaticDataPort{
  typedef StaticDataPort<container,flag::value> type;
};



}//namespace
}//namespace

#endif
