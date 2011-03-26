
#ifdef KIWI_DO_INCLUDE_STATICWRITERPORT_DEF_HPP
#ifndef KIWI_CORE_STATICWRITERPORT_DEF_HPP
#define KIWI_CORE_STATICWRITERPORT_DEF_HPP

namespace kiwi{
namespace core{

template<typename ContainerType, class ConnectionPolicy>
void StaticWriterPort<ContainerType,ConnectionPolicy>::autoAllocateNode(){
  ScopedBlockMacro("StaticWriterPort::autoAllocateNode")
  if( !isConnected() ){
    _container = new ContainerType;
    _auxNode = new DynamicContainerNode( _container, new StaticDataPort<ContainerType>(_container),  true);
    assert( connect( &_auxNode->dataPort() ) );
  }
}


}//namespace
}//namespace


#endif
#endif
