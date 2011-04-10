
#ifndef KIWI_CORE_DYNAMICNODELAYOUT_HPP
#define KIWI_CORE_DYNAMICNODELAYOUT_HPP

#include "kiwi/core/StaticPorts.hpp"

namespace kiwi{
namespace core{

class DynamicNodeLayout{
public:

  template<typename ContainerType>
  void createReader( ContainerType* ptr ) {
    _readerPorts.push_back( new StaticReaderPort<ContainerType>( ptr );
  }
  template<typename ContainerType>
  void createWriter( ContainerType* ptr ) {
    _WriterPorts.push_back( new StaticWriterPort<ContainerType>( ptr );
  }
  stemplate<typename ContainerType>
  void addData( ContainerType* ) {
    
  }
protected:
  std::vector<ReaderPort*> _readerPorts;
  std::vector<WriterPort*> _writerPorts;
  std::vector<dataPort*> _dataPorts;
};


}//namespace
}//namespace



#endif
