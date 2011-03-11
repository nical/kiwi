
#pragma once
#ifndef KIWI_CORE_TEMPLATEREADERPORT_HPP
#define KIWI_CORE_TEMPLATEREADERPORT_HPP

#include "kiwi/core/ReaderPort.hpp"

namespace kiwi{
namespace core{

template<class TContainerType>
class TReaderPort : public ReaderPort
{
public:
  typedef TContainerType ContainerType;

  TReaderPort(kiwi::core::Node* myNode)
  : ReaderPort(myNode), _tcontainer(0){}

  ContainerType* getContainer() const{
    return _tcontainer;
  }

  void updatePort(){
    ScopedBlockMacro(scop,"TReaderPort::updatePort")
    Debug::plop(); 
    if( isConnected() )
      _tcontainer = connectedPort()->safeDownCastContainer<ContainerType>();
    DEBUG_ONLY( else Debug::error() << "this port is not connected\n"; )
    DEBUG_ONLY( if(!_tcontainer) Debug::error() << "update failed\n"; )
  }

  

	/**
	 * @brief returns true if this port is enabled.
	 * 
	 * A port as to be enabloed to be connected. 
	 * By default a port is enabled.
	 */ 
	//virtual bool isEnabled() const ;
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
