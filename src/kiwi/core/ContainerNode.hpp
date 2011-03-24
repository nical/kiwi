
#pragma once
#ifndef KIWI_CORE_CONTAINERNODE_HPP
#define KIWI_CORE_CONTAINERNODE_HPP

#include "kiwi/core/Node.hpp"
#include "kiwi/core/StaticNode.hpp"

namespace kiwi{
namespace core{


template<class ContainerType>
struct ContainerNodeStaticLayout{
  typedef StaticNodeLayout<
    ReaderListMacro< > ,
    WriterListMacro< > ,
    DataListMacro< StaticDataPort<Container> >
  > type;
};

template<class TContainerType>
class ContainerNode
: public StaticNode< typename ContainerNodeStaticLayout<TContainerType>::type >
{
public:
  typedef TContainerType  ContainerType;

  ContainerNode( ContainerType* container, bool deleteContainerOnDestruction = false ) : _container( container ), _deleteContainer(deleteContainerOnDestruction){}

  ~ContainerNode(){
    if(_deleteContainer) delete _container;
  }

protected:
  ContainerType* _container;
  bool _deleteContainer;
};


}//namespace
}//namespace


#endif
