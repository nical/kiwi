//here for cyclic dependency issues
//#include "kiwi/core/ContainerNode.hpp"

#pragma once
#ifndef KIWI_CORE_TEMPLATEWRITERPORT_HPP
#define KIWI_CORE_TEMPLATEWRITERPORT_HPP

#include "kiwi/core/WriterPort.hpp"
#include "kiwi/core/AlwaysCompatibleConnectionPolicy.hpp"
#include "kiwi/core/DynamicContainerNode.hpp"


namespace kiwi{
namespace core{

template<class TContainerType
  , class ConnectionPolicy = AlwaysCompatibleConnectionPolicy>
class StaticWriterPort : public WriterPort
{
public:
  typedef TContainerType ContainerType;

  StaticWriterPort(kiwi::core::Node* myNode = 0)
  : WriterPort(myNode), _container(0){}

  void setNode( kiwi::core::Node * const node){ _node = node; }

  ContainerType* getAbstractContainer() const{
    return _container;
  }
  
  ContainerType* getContainer(){
    if( isConnected() ){
      return _container;
    }else{
      //if( isAssociatedToDataPort() ){
        autoAllocateNode();
      //}

    return 0;
    }
  }

  void updatePort(){
    ScopedBlockMacro("StaticWriterPort::updatePort")
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

  void autoAllocateNode();
  

protected:

  ContainerType* _container;
  Node* _auxNode;
};


}//namespace
}//namespace


#endif
