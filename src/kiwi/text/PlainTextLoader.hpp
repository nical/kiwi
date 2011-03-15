#pragma once
#ifndef KIWI_TEXT_PLAINTEXTLOADER_HPP
#define KIWI_TEXT_PLAINTEXTLOADER_HPP

#include "kiwi/core/Filter.hpp"
#include "kiwi/core/DataPort.hpp"
#include "kiwi/core/TReaderPort.hpp"
#include "kiwi/core/TWriterPort.hpp"
#include "kiwi/text/TextContainerInterface.hpp"
#include "kiwi/text/PlainTextContainer.hpp"
#include "kiwi/text/PlainTextLine.hpp"
#include "kiwi/utils/Factory.hpp"

#include <fstream>

namespace kiwi{
namespace text{


class PlainTextLoader : public kiwi::core::Filter
{
public:
  PlainTextLoader(){
    addReaderPort(
      _inputPath = new kiwi::core::TReaderPort<TextContainerInterface>(this));
    addWriterPort(
      _outputText = new kiwi::core::TWriterPort<TextContainerInterface>(this));
    addDataPort();
    associateWriterToDataPort( *_outputText, dataPort(0) );

    _auxNode = 0;
  }

  ~PlainTextLoader(){
    if(_auxNode) delete _auxNode;
  }

  void process(){
    ScopedBlockMacro(scop,"PlainTextLoader::process")
    if( !_outputText->isConnected() ){
      _auxNode = new kiwi::core::Node( new PlainTextContainer );
      _auxNode->dataPort() >> writerPort();
      assert( _outputText->isConnected() );
    }
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
      //release the system resource
      file.close();
    }else{
      Debug::error() << "file not found\n";
    }
  }

  kiwi::utils::Tags readerTags( portIndex_t index ) const {
		return kiwi::utils::Tags("#text"); // TODO #path ?
	}

  kiwi::utils::Tags writerTags( portIndex_t index ) const	{
		return kiwi::utils::Tags("#text");
	}

  
  static Node* newPlainTextLoader() { return new PlainTextLoader; }
	
	static bool registerToFactory(kiwi::utils::NodeFactory& factory, const kiwi::string& filterId)
	{
		factory.registerClass( filterId
    , kiwi::utils::NodeFactoryDescriptor(	newPlainTextLoader, "#Filter#Loader#text" )
    );	
		return true;
	}

protected:
kiwi::core::Node* _auxNode;
kiwi::core::TReaderPort<TextContainerInterface>* _inputPath;
kiwi::core::TWriterPort<TextContainerInterface>* _outputText;
};



}//namespace
}//namespace






#endif
