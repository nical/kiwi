
#include "AbstractAccessPort.hpp"
#include "AbstractDataPort.hpp"
#include "kiwi/utils/DebugStream.hpp"


namespace kiwi{
namespace core{



bool AbstractAccessPort::connect(AbstractDataPort& port ){
  SCOPEDBLOCK_MACRO("AbstractAccessPort::connect");
  if( isCompatible(port) ){
    if( isConnected() ) disconnect();
    // for now we don't handle a maximum amount of connections for data ports
    _connectedPort = &port;
    port._connectedPorts.insert(this);
    return true;
  }
  return false;
}

void AbstractAccessPort::disconnect(){
  SCOPEDBLOCK_MACRO("AbstractAccessPort::connect");
  if(_connectedPort){
    _connectedPort->_disconnect(this);
    _connectedPort = 0;
  }
}

}//namespace
}//namespace
