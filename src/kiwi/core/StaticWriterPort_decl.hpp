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
     return getContainer();
  }
  
  ContainerType* getContainer(){
    if( isConnected() ){
      return _container;
    }else{
      autoAllocateNode();
      return _container;
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
	virtual bool isCompatible(DataPort& port) const {
    return ConnectionPolicy::isCompatible( *this, port );
  }

  void autoAllocateNode();
  

protected:

  ContainerType* _container;
  Node* _auxNode;
};


}//namespace
}//namespace


#endif
