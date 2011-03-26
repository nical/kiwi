
#include "kiwi/core/DynamicContainerNode.hpp"
#include "kiwi/core/DataPort.hpp"

namespace kiwi{
namespace core{

DynamicContainerNode::DynamicContainerNode(
  Container* container
  , DataPort* port
  , bool deleteContainer )
{
  _port = port;
  _port->setNode(this);
  _container = container;
  assert(_port);
  assert( _port->getAbstractContainer() );
  _deleteContainer = deleteContainer;
}

DataPort& DynamicContainerNode::dataPort(portIndex_t) const{
  return *_port;
}

ReaderPort& DynamicContainerNode::readerPort(portIndex_t) const{
  assert("DynamicContainerNode::readerPort: error" == "DynamicContainerNode do not have reader ports.");
}

WriterPort& DynamicContainerNode::writerPort(portIndex_t) const{
  assert("DynamicContainerNode::writerPort: error" == "DynamicContainerNode do not have writer ports.");
}

}//namespace
}//namespace
