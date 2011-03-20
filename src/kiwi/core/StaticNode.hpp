
#ifndef KIWI_CORE_STATICNODE_HPP
#define KIWI_CORE_STATICNODE_HPP

#include <vector>
#include <boost/fusion/include/sequence.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/mpl.hpp>

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
  template<typename T> void operator()(const T& port) const {
    const_cast<T&>(port).setNode(_node); }
  
  NodeType* _node;
};

template<typename PortType>
struct PortDynamicAccessWrapper{
  PortDynamicAccessWrapper(std::vector<PortType*>& array) : _array(&array){}
  template<typename T> void operator()(const T& port) const {
    _array->push_back( &const_cast<T&>(port) ); }
  
  std::vector<PortType*>* _array;
};


template<typename TReaderList, typename TWriterList, typename TDataList>
struct StaticNodeLayout{
  typedef TReaderList ReaderList;
  typedef TWriterList WriterList;
  typedef TDataList DataList;
  typedef StaticNodeLayout<ReaderList,WriterList,DataList> Self;
  
  StaticNodeLayout(kiwi::core::StaticNode<Self>* node){
  // set each port's associated Node to node  
    boost::fusion::for_each(
      boost::fusion::as_vector(_readerPorts), PortNodeSetter<Node>(node) );
    boost::fusion::for_each(
      boost::fusion::as_vector(_writerPorts), PortNodeSetter<Node>(node) );
    boost::fusion::for_each(
      boost::fusion::as_vector(_dataPorts)  , PortNodeSetter<Node>(node) );
  // then fill the vectors containing higher level access to ports
    boost::fusion::for_each( boost::fusion::as_vector(_readerPorts)
      , PortDynamicAccessWrapper<ReaderPort>(_dynReaderPorts) );
    boost::fusion::for_each( boost::fusion::as_vector(_writerPorts)
      , PortDynamicAccessWrapper<WriterPort>(_dynWriterPorts) );
    boost::fusion::for_each( boost::fusion::as_vector(_dataPorts)
      , PortDynamicAccessWrapper<DataPort>(_dynDataPorts) );
      
  }

  ReaderList _readerPorts;
  WriterList _writerPorts;
  DataList   _dataPorts;

  std::vector<ReaderPort*> _dynReaderPorts;
  std::vector<WriterPort*> _dynWriterPorts;
  std::vector<DataPort*> _dynDataPorts;
};


template<typename TLayout>
class StaticNode : public kiwi::core::Node
{
public:
  typedef TLayout Layout;

  StaticNode() : _layout(this){}

  template<int i> struct staticReaderPort{
    typedef typename boost::mpl::at<typename Layout::ReaderList,boost::mpl::arg<i> >::type type;
    type& get() { return boost::fusion::at_c<i>(_layout._readerPorts); }
  };

protected:
  Layout _layout;
};





}//namespace
}//namespace


#endif


