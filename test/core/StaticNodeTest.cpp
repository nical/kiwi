

#include "kiwi/core/StaticNode.hpp"
#include "kiwi/core/Commons.hpp"
#include "kiwi/core/Container.hpp"

//typedef boost::fusion::vector reader_list;
#define reader_list boost::fusion::vector
#define writer_list boost::fusion::vector
#define data_list boost::fusion::vector



class A : public kiwi::core::Container {};
class B : public kiwi::core::Container {};
class C : public kiwi::core::Container {};


typedef kiwi::core::StaticNodeLayout<
    reader_list<
      kiwi::core::StaticReaderPort<A>
    , kiwi::core::StaticReaderPort<B>
    , kiwi::core::StaticReaderPort<C> >
  , writer_list<
      kiwi::core::StaticWriterPort<B>
    , kiwi::core::StaticWriterPort<C> >
  , data_list<
      kiwi::core::StaticDataPort<A> >
> myLayout;



int main(){
  ScopedBlockMacro("StaticNode::Test")

  myLayout layout(0);

  typedef kiwi::core::StaticNode<myLayout> myNode;
  myNode node;

  myNode::staticReaderPortInfo<1>::type& aPort = node.staticReaderPort<1>();

  kiwi::Debug::print() << (int)((kiwi::core::ReaderPort*)&node.staticReaderPort<0>()) - (int)&node.readerPort(0) << "\n";
  kiwi::Debug::print() << (int)((kiwi::core::ReaderPort*)&node.staticReaderPort<1>()) - (int)&node.readerPort(1) << "\n";
  kiwi::Debug::print() << (int)((kiwi::core::ReaderPort*)&node.staticReaderPort<2>()) - (int)&node.readerPort(2) << "\n";

  kiwi::core::StaticReaderPort<A>* srpTest = new kiwi::core::StaticReaderPort<A>(0);
  kiwi::core::ReaderPort* srpTestBis = srpTest;
  assert( (int)srpTest - (int)srpTestBis == 0 );
  
  assert( &node.staticReaderPort<0>() == &node.readerPort(0) );
  assert( &node.staticReaderPort<1>() == &node.readerPort(1) );
  assert( &node.staticReaderPort<2>() == &node.readerPort(2) );
  assert( &node.staticWriterPort<0>() == &node.writerPort(0) );
  assert( &node.staticWriterPort<1>() == &node.writerPort(1) );
  assert(  &node.staticDataPort<0>()  == &node.dataPort(0) );
  
}
