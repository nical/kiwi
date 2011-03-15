#pragma once
#ifndef KIWI_TEXT_PLAINTEXTLOADER_HPP
#define KIWI_TEXT_PLAINTEXTLOADER_HPP

#include "kiwi/core/Filter.hpp"
#include "kiwi/core/DataPort.hpp"
#include "kiwi/core/TReaderPort.hpp"
#include "kiwi/core/TWriterPort.hpp"
#include "kiwi/text/TextContainerInterface.hpp"

#include <fstream>

namespace kiwi{
namespace text{


class PlainTextLoader : public kiwi::core::Filter
{
public:
  PlainTextLoader(){
    _inputPath = new kiwi::core::TReaderPort<TextContainerInterface>(this);
    _outputText = new kiwi::core::TWriterPort<TextContainerInterface>(this);
    addDataPort();
    associateWriterToDataPort( *_outputText, dataPort(0) );
  }

  void process(){
    ScopedBlockMacro(scop,"PlainTextLoader::process")
    TextContainerInterface* input = _inputPath->getContainer();
    TextContainerInterface* output = _outputText->getContainer();
    assert(input);
    assert(output);
    std::ifstream file( input->line(0).str().c_str() );
    if( file.is_open() ) {
      //init
      while( !file.eof() ){
        kiwi::string line;
        std::getline(file, line);
        output->insertLine( PlainTextLine(line), output->nbLines() );
      }
      //release the stream
      file.close();
    }else{
      Debug::error() << "file not found\n";
    }
  }

  ~PlainTextLoader(){
    //delete _inputPath;
    //delete _outputText;
  }
  

protected:
kiwi::core::TReaderPort<TextContainerInterface>* _inputPath;
kiwi::core::TWriterPort<TextContainerInterface>* _outputText;
};



}//namespace
}//namespace






#endif
