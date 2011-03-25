
#pragma once
#ifndef KIWI_CORE_DYNAMICCONTAINERNODE_HPP
#define KIWI_CORE_DYNAMICCONTAINERNODE_HPP

#include "kiwi/core/Node.hpp"

namespace kiwi{
namespace core{

class DynamicContainerNode : public core::Node
{
public:

  DynamicContainerNode( Container* container, DataPort* port, bool deleteContainer = false );

  DataPort& dataPort(portIndex_t = 0) const;
  ReaderPort& readerPort(portIndex_t index = 0) const;
	WriterPort& writerPort(portIndex_t index = 0) const;

  portIndex_t nbReaderPorts() const { return 0; }
  portIndex_t nbWriterPorts() const { return 0; }
  portIndex_t nbDataPorts() const { return 1; }

protected:
  Container* _container;
  DataPort* _port;
  bool _deleteContainer;
};

}//namespace
}//namespace



#endif
