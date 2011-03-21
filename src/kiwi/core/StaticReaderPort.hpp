
#pragma once
#ifndef KIWI_CORE_TEMPLATEREADERPORT_HPP
#define KIWI_CORE_TEMPLATEREADERPORT_HPP

#include "kiwi/core/ReaderPort.hpp"

namespace kiwi{
namespace core{

template<class TContainerType>
class StaticReaderPort : public ReaderPort
{
public:
  typedef TContainerType ContainerType;

  StaticReaderPort(kiwi::core::Node* myNode = 0)
  : ReaderPort(myNode), _tcontainer(0){}

  void setNode( kiwi::core::Node* const node){ _node = node; }

  const Container* getAbstractContainer() const{
    return _tcontainer;
  }
  
  ContainerType* getContainer() const{
    return _tcontainer;
  }

  void updatePort(){
    ScopedBlockMacro("StaticReaderPort::updatePort")
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
    if( !port.isEmpty() ){
      return port.safeDownCastContainer<ContainerType>();
    }else{
      // TODO: right now the dynamic_cast method works only when the data port
      // already has an allocated container, which is a problem.
      // So we fall back to the old tag compatibility method
      // this hack is temporary. 
      return ( port.tags().hasOneOf( tags() ) );
    }
  }

protected:

  //void connect_impl( DataPort* port );
  //void disconnect_impl( DataPort* port );

  ContainerType* _tcontainer;
};


}//namespace
}//namespace


#endif
