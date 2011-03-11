
#pragma once
#ifndef KIWI_CORE_TEMPLATEWRITERPORT_HPP
#define KIWI_CORE_TEMPLATEWRITERPORT_HPP

#include "kiwi/core/WriterPort.hpp"

namespace kiwi{
namespace core{

template<class TContainerType>
class TWriterPort : public WriterPort
{
public:
  typedef TContainerType ContainerType;

  TWriterPort(kiwi::core::Node* myNode)
  : WriterPort(myNode), _tcontainer(0){}

  ContainerType* getAbstractContainer() const{
    return _tcontainer;
  }
  
  ContainerType* getContainer() const{
    return _tcontainer;
  }

  void updatePort(){
    ScopedBlockMacro(scop,"TWriterPort::updatePort")
    Debug::plop(); 
    if( isConnected() )
      _tcontainer = connectedPort()->safeDownCastContainer<ContainerType>();
    DEBUG_ONLY( else Debug::error() << "this port is not connected\n"; )
    DEBUG_ONLY( if(!_tcontainer) Debug::error() << "update failed\n"; )
  }

  
	/**
	 * @brief Port compatibility check based on the type tag.
	 */ 
	virtual bool isCompatible(DataPort& port){
    return port.safeDownCastContainer<ContainerType>();
  }

protected:

  //void connect_impl( DataPort* port );
  //void disconnect_impl( DataPort* port );

  ContainerType* _tcontainer;
};


}//namespace
}//namespace


#endif
