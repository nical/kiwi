
#include "AbstractDataPort.hpp"
#include "kiwi/utils/DebugStream.hpp"

namespace kiwi{
namespace core{

void AbstractDataPort::disconnect( AbstractAccessPort* port ){
  SCOPEDBLOCK_MACRO("AbstractDataPort::disconnect");
  if( port == 0 ){
    ConnectedPortsSeq::iterator it = _connectedPorts.begin();
    ConnectedPortsSeq::iterator stop = _connectedPorts.end();
    for(;it!=stop;++it){
      (*it)->disconnect();
    }
  }else if( _connectedPorts.has(port) ){
    out << "has port" << endl;
    port->disconnect();
  }
}

void AbstractDataPort::_disconnect( AbstractAccessPort* port ){
  if(port) _connectedPorts.remove(port);
  else _connectedPorts.clear();
  
}


}//namespace
}//namespace
