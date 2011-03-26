
#pragma once
#ifndef KIWI_CORE_TEMPLATEREADERPORT_HPP
#define KIWI_CORE_TEMPLATEREADERPORT_HPP

#include "kiwi/core/ReaderPort.hpp"
#include "kiwi/core/AlwaysCompatibleConnectionPolicy.hpp"

namespace kiwi{
namespace core{


template<class TContainerType
  , class ConnectionPolicy = AlwaysCompatibleConnectionPolicy>
class StaticReaderPort : public ReaderPort
{
public:
  typedef TContainerType ContainerType;

  StaticReaderPort(kiwi::core::Node* myNode = 0)
  : ReaderPort(myNode), _container(0){}

  void setNode( kiwi::core::Node* const node ){ _node = node; }

  bool isCompatible( const DataPort& port ) const {
    ScopedBlockMacro("StaticReaderPort::isCompatible")
    return ConnectionPolicy::isCompatible( *this, port );
  }

  const Container* getAbstractContainer() const {
    return _container;
  }
  
  ContainerType* getContainer() const {
    return _container;
  }

  void updatePort(){
    ScopedBlockMacro("StaticReaderPort::updatePort")
    Debug::plop(); 
    if( isConnected() )
      _container = connectedPort()->safeDownCastContainer<ContainerType>();
    DEBUG_ONLY( else Debug::error() << "this port is not connected\n"; )
    DEBUG_ONLY( if(!_container) Debug::error() << "update failed\n"; )
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

  ContainerType* _container;
  ConnectionPolicy _policy;
};





}//namespace
}//namespace


#endif
