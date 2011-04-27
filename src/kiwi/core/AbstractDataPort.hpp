
#ifndef KIWI_CORE_ABSTRACTDATAPORT_HPP
#define KIWI_CORE_ABSTRACTDATAPORT_HPP
#pragma once

#include "kiwi/utils/UnorderedArray.hpp"
#include "kiwi/core/AbstractAccessPort.hpp"

namespace kiwi{
namespace core{



class AbstractDataPort{
public:
  void commit();
  void disconnect( AbstractAccessPort* = 0 );
  void disconnectAll( AccessFlag flag = READ_WRITE );

  
  // inline methods
  bool connect( AbstractAccessPort& port ) { return port.connect(*this); }
  bool isCompatible( AbstractAccessPort& port ){ return port.isCompatible(*this); }
  kiwi::int32 nbConnections() const { return _connectedPorts.size(); }
  bool isConnected(AbstractAccessPort& port) const { return _connectedPorts.find(&port); }
  bool isConnected() const { return nbConnections(); }
 
  // virtual methods
  virtual AccessFlag flag() const = 0;
  
  
protected:
  utils::UnorderedArray<AbstractAccessPort*> _connectedPorts;
};


}//namespace
}//namespace



#endif
