
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

}//namespace
}//namespace
