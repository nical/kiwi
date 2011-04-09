
#ifndef KIWI_DUMMY_FILTER_HPP
#define KIWI_DUMMY_FILTER_HPP

#include "Filter.hpp"
#include "DynamicNodeLayout.hpp"

class DummyContainerA { };
class DummyContainerB { };

class DummyFilter : public kiwi::core::Filter{
public:
  void process(){
    // PROCESS
    // use _readA, etc.
  }
  
protected:
  SetupLayout( DynamicNodeLayout& layout ){
    layout.createReader( _readA );
    layout.createReader( _readB );
    layout.createWriter( _write );
  }
private:
  DummyContainerA* _readA;
  DummyContainerB* _readB;
  DummyContainerA* _Write;
};



class StaticDummyFilter : public kiwi::core::Filter{
public:
  void process(){
    // PROCESS
    // use _readA, etc.
  }

  
template<typename ContainerType, int index> ContainerType* getReaderPtr(){};
template<> DummyContainerA* _getReaderPtr<DummyContainerA,0>(){return _readA;};
template<> DummyContainerB* _getReaderPtr<DummyContainerB,1>(){return _readB;};
template<typename ContainerType, int index> ContainerType* getWriterPtr(){};
template<> DummyContainerB* _getWriterPtr<DummyContainerB,2>(){return _write;};
// ReaderContainerMacro
// ReaderContainerPointer(DummyContainerA,0,_readA)
// |  template<> DummyContainerA*
// |     _getReaderPtr<DummyContainerA,0>(){return _readA;};
// |  typedef DummyContainerA _readerType0; 
private:
  DummyContainerA* _readA;
  DummyContainerB* _readB;
  DummyContainerA* _Write;
};

/* Then:
 *
 * SNType aStaticNode = makeStaticNode<StaticDymmyFilter>(StaticDummyFilter)
 */ 

#endif
