
#pragma once
#ifndef KIWI_CORE_TEMPLATEDATAPORT_HPP
#define KIWI_CORE_TEMPLATEDATAPORT_HPP

#include "kiwi/core/DataPort.hpp"

namespace kiwi{
namespace core{


template<class TContainerType = kiwi::core::Container, int TFlag = 3>
class StaticDataPort : public DataPort
{
public:
  typedef TContainerType ContainerType;
  enum { READ = 1, WRITE = 2, READ_WRITE = READ || WRITE, Flag = TFlag };

  StaticDataPort() : DataPort(0) {}
  StaticDataPort(ContainerType* container)
  : DataPort(0), _container(container) {}
  
  
  StaticDataPort(Node* myNode, ContainerType* data = 0)
  : DataPort( myNode ){_container = data;}

  void setNode( kiwi::core::Node* const node){ _node = node; }

  virtual Container* getAbstractContainer() const {
    return _container;
  }

  ContainerType* getContainer() const {
    return _container;
  }

  int flag() const { return TFlag; }

  virtual bool isEmpty() const{
    return (getAbstractContainer() == 0);
  }

  virtual bool setAbstractContainer( Container* data )
  {
    // set the container
    _container = dynamic_cast<ContainerType*>(data);
    // transmit the modification to the ports that are bound to this port. 
    for(kiwi::int32_t i = 0; i < _slaveLinkedDataPorts.size(); ++i)
      callSetAbstractContainer(*_slaveLinkedDataPorts[i], data );
    // return true if it worked for this port
    return _container != 0;
  }
  
  virtual bool setContainer( ContainerType* data ){
    // set the container
    _container = data;
    // transmit the modification to the ports that are bound to this port. 
    for(kiwi::int32_t i = 0; i < _slaveLinkedDataPorts.size(); ++i)
      callSetAbstractContainer(*_slaveLinkedDataPorts[i], data );
    // returns true unless the input argument was a nil pointer
    return _container != 0;
  }

  // implemented in StaticDataPort_def.hpp
  template<typename T1, typename policy>
  bool operator >> ( StaticReaderPort<T1, policy>& readerPort );

  // implemented in StaticDataPort_def.hpp
  template<typename T1, typename policy>
  bool operator >> ( StaticWriterPort<T1,policy>& writerPort );

protected:
  ContainerType* _container;
};


}//namespace
}//namespace


#endif

/*
* from sequence of container types
* -> make a sequence of StaticDataPorts of these container types
* (mpl::vector<image,text>
*   --> fusion::vector<StaticDataPort<image>,StaticDataPort<image> > )
* 

struct MySubPorts{
  typedef StaticDataPort<image> t0; t0 n0;
  typedef StaticDataPort<text> t1; t1 n1;
}; 
struct MySubPorts2{
  SubPortMacro( StaticDataPort<image>, 0 );
  SubPortMacro( StaticDataPort<text>, 1 );
};

#define SubPortMacro(name,num) typedef name t##num; t##num n##num;
*/
