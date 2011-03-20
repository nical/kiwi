
#pragma once
#ifndef KIWI_CORE_TEMPLATEDATAPORT_HPP
#define KIWI_CORE_TEMPLATEDATAPORT_HPP

#include "kiwi/core/DataPort.hpp"

namespace kiwi{
namespace core{

template<class TContainerType>
class TDataPort : public DataPort
{
public:
  typedef TContainerType ContainerType;

  TDataPort() : DataPort(0,0) {}

  void setNode( kiwi::core::Node* const node){ _node = node; }

  TDataPort(Node* myNode, ContainerType* data = 0)
  : DataPort(myNode, data ){_tcontainer = data;}

  virtual Container* getAbstractContainer() const {
    return _tcontainer;
  }

  ContainerType* getContainer() const {
    return _tcontainer;
  }

protected:

  ContainerType* _tcontainer;
};


}//namespace
}//namespace


#endif
