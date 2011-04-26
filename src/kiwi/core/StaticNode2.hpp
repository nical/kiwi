
#ifndef KIWI_CORE_STATICNODE_HPP_
#define KIWI_CORE_STATICNODE_HPP_

#include "kiwi/mpl/TypeList.hpp"
#include "kiwi/mpl/Tuple.hpp"
#include "kiwi/mpl/TupleApplyFunctor.hpp"

namespace kiwi{
namespace core{



template<typename NodeType> struct PortNodeSetter{
  PortNodeSetter(NodeType* node) : _node(node){}
  template<typename T> void operator()(const T& port) const {
    const_cast<T&>(port).setNode(_node); }
  NodeType* _node;
};



template<typename TReaderTypeList, typename TWriterTypeList, typename TDataTypeList>
struct StaticNodeLayout{
  // typedefs
  typedef TReaderTypeList ReaderTypeList;
  typedef TWriterTypeList WriterTypeList;
  typedef TDataTypeList   DataTypeList;
  typedef StaticNodeLayout<ReaderTypeList,WriterTypeList,DataTypeList> Self;
  typedef kiwi::mpl::Tuple<ReaderTypeList> ReaderTuple;
  typedef kiwi::mpl::Tuple<WriterTypeList> WriterTuple;
  typedef kiwi::mpl::Tuple<DataTypeList>   DataTuple;
  //methods
  StaticNodeLayout(kiwi::core::Node* node){
    // TODO: port node setter
    // TODO: dynAccessWrapper
  }

  // data
  ReaderTuple _staticReaderPorts;
  WriterTuple _staticWriterPorts;
  DataTuple _staticDataPorts;
  ReaderPort*[ReaderList::size] _dynReaderPorts;
  WriterPort*[WriterList::size] _dynWriterPorts;
  WriterPort*[DataList::size] _dynDataPorts;
};


template<typename TLayout>
class StaticNode_{


};



}//namespace
}//namespace

#endif
