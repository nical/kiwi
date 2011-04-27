
#include "AbstractDataPort.hpp"

namespace kiwi{
namespace core{

void AbstractDataPort::disconnect( AbstractAccessPort* port ){
  if( _connectedPorts.find(port) )
    port->disconnect();
}

void AbstractDataPort::_disconnect( AbstractAccessPort* port ){
  if(port) _connectedPorts.remove(port);
  else _connectedPorts.clear();
  
}


}//namespace
}//namespace
