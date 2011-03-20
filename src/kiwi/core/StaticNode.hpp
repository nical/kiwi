
#ifndef KIWI_CORE_STATICNODE_HPP
#define KIWI_CORE_STATICNODE_HPP

#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/for_each.hpp>
#include "kiwi/core/TReaderPort.hpp"
#include "kiwi/core/TWriterPort.hpp"
#include "kiwi/core/TDataPort.hpp"
#include "kiwi/core/Node.hpp"

namespace kiwi{
namespace core{

class Node;

template<typename TLayout> class StaticNode;

template<typename NodeType>
struct PortNodeSetter{
  PortNodeSetter(NodeType* node) : _node(node){}
  template<typename T> void operator()(const TReaderPort<T>& port) const {
    const_cast< TReaderPort<T>& >(port).setNode(_node); }
  template<typename T> void operator()(const TWriterPort<T>& port) const {
    const_cast< TWriterPort<T>& >(port).setNode(_node); }
  template<typename T> void operator()(const TDataPort<T>& port) const {
    const_cast< TDataPort<T>& >(port).setNode(_node); }
  NodeType* _node;
};


template<typename TReaderList, typename TWriterList, typename TDataList>
struct StaticNodeLayout{
  typedef TReaderList ReaderList;
  typedef TWriterList WriterList;
  typedef TDataList DataList;
  typedef StaticNodeLayout<ReaderList,WriterList,DataList> Self;
  
  StaticNodeLayout(kiwi::core::StaticNode<Self>* node){
    boost::fusion::for_each(
      _readerPorts, PortNodeSetter<Node>(node) );
    boost::fusion::for_each(
      boost::fusion::as_vector(_writerPorts), PortNodeSetter<Node>(node) );
    boost::fusion::for_each(
      boost::fusion::as_vector(_dataPorts)  , PortNodeSetter<Node>(node) );
  }

  ReaderList _readerPorts;
  WriterList _writerPorts;
  DataList   _dataPorts;

};


template<typename TLayout>
class StaticNode : public kiwi::core::Node
{
public:
  typedef TLayout Layout;

protected:
  Layout _layout;
};





}//namespace
}//namespace


#endif


