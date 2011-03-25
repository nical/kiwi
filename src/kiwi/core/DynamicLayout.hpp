
#pragma once
#ifndef KIWI_CORE_DYNAMICLAYOUT_HPP
#define KIWI_CORE_DYNAMICLAYOUT_HPP

namespace kiwi{
namespace core{

class ReaderPort;
class WriterPort;
class DataPort;

class DynamicLayout{
public:
  addReaderPort( kiwi::core::ReaderPort* newPort );
  addWriterPort( kiwi::core::WriterPort* newPort );
  addDataPort( kiwi::core::DataPort* newPort );

std::vector<kiwi::core::ReaderPort*> _readerPorts;
std::vector<kiwi::core::WriterPort*> _writerPorts;
std::vector<kiwi::core::DataPort*> _dataPorts;
};



}//namespace  
}//namespace  

#endif
