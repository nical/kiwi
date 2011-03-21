

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
  
}
