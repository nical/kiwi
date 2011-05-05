#pragma once
#ifndef KIWI_CORE_STATICDATAPORT_DECL_HPP
#define KIWI_CORE_STATICDATAPORT_DECL_HPP

#include "AbstractDataPort.hpp"
#include "Container.hpp"

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



template<typename TContainerType, AccessFlag TAccessFlag>
class StaticDataPort : public AbstractDataPort
{
public:
  static const AccessFlag Flag = TAccessFlag;
  typedef TContainerType ContainerType;
  
  AccessFlag flag() const { return Flag; }

  typename ApplyConstModifier<ContainerType,Flag>::type * container() { return _container; }
  Container* abstractContainer() { return _container; }
  
protected:  
  ContainerType* _container;
};





}//namespace
}//namespace

#endif
