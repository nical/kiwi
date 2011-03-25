
#include "kiwi/core/DynamicContainerNode.hpp"


namespace kiwi{
namespace core{

DynamicContainerNode::DynamicContainerNode(
  Container* container
  , DataPort* port
  , bool deleteContainer )
{
  _port = port;
  _container = container;
  assert(port);
  _deleteContainer = deleteContainer;
}

DataPort& DynamicContainerNode::dataPort(portIndex_t) const{
  return *_port;
}

ReaderPort& DynamicContainerNode::readerPort(portIndex_t) const{
  assert("error" == "DynamicContainerNode do not have reader ports.");
}

WriterPort& DynamicContainerNode::writerPort(portIndex_t) const{
  assert("error" == "DynamicContainerNode do not have writer ports.");
}

}//namespace
}//namespace
