#pragma once
#ifndef KIWI_CORE_DYNAMICDATAPORT_HPP
#define KIWI_CORE_DYNAMICDATAPORT_HPP

#include "kiwi/core/ContainerManager.hpp"
#include "kiwi/core/AbstractDataPort.hpp"

namespace kiwi{
namespace core{



class DynamicDataPort : AbstractDataPort{
public:
  DynamicDataPort(kiwi::int32 containerInfoId = 0, AccessFlag flag = READ_WRITE)
  : _containerInfo(containerInfoId), _flag(flag){
    _container = 0;
    _motherPort = 0;
  }
  
  // ---------------------------------------------------------------------------

  // ------------------------------------------------------------ inline methods
  bool setContainerInfo(kiwi::int32 containerInfoId){
    _containerInfo = containerInfoId;
  }
  AccessFlag flag() const { return _flag; }
  AbstractContainer* abstractContainer() { return _container; }

  // ---------------------------------------------------------------------------  
protected:
  /**
   * SubPort constructor.
   */ 
  DynamicDataPort(
    kiwi::int32 containerInfoId 
    , AccessFlag flag
    , DynamicDataPort* parentPortPtr );

  void initSubPorts(
    kiwi::int32 containerInfoId 
    , AccessFlag flag
    , DynamicDataPort* parentPortPtr);


  kiwi::int32 _containerInfo;
  AccessFlag _flag;
  AbstractContainer* _container;
  std::vector<DynamicDataPort*> _subPorts;
  DynamicDataPort* _motherPort;
};




}//namespace
}//namespace



#endif
