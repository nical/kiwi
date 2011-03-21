
#pragma once
#ifndef KIWI_CORE_TEMPLATEDATAPORT_HPP
#define KIWI_CORE_TEMPLATEDATAPORT_HPP

#include "kiwi/core/DataPort.hpp"

namespace kiwi{
namespace core{

template<class TContainerType, int TFlag = 3>
class StaticDataPort : public DataPort
{
public:
  typedef TContainerType ContainerType;
  //static const int Flag; 
  enum { READ = 1, WRITE = 2, READ_WRITE = READ || WRITE, Flag = TFlag };

  StaticDataPort() : DataPort(0,0) {}

  void setNode( kiwi::core::Node* const node){ _node = node; }

  StaticDataPort(Node* myNode, ContainerType* data = 0)
  : DataPort( myNode, data ){_tcontainer = data;}

  virtual Container* getAbstractContainer() const {
    return _tcontainer;
  }

  ContainerType* getContainer() const {
    return _tcontainer;
  }

  int flag() const { return TFlag; }

protected:

  ContainerType* _tcontainer;
};


}//namespace
}//namespace


#endif
