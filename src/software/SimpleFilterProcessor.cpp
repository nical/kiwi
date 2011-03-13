// Copyright (c) 2010 Nicolas Silva
// All rights reserved.
//      Redistribution and use in source and binary forms, with or without
//      modification, are permitted provided that the following conditions are
//      met:
//      
//      * Redistributions of source code must retain the above copyright
//        notice, this list of conditions and the following disclaimer.
//      * Redistributions in binary form must reproduce the above
//        copyright notice, this list of conditions and the following disclaimer
//        in the documentation and/or other materials provided with the
//        distribution.
//      * Neither the name of the  nor the names of its
//        contributors may be used to endorse or promote products derived from
//        this software without specific prior written permission.
//      
//      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//      "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//      LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//      A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//      OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//      SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//      LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//      DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//      THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//      OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

/**
 * @file SimpleFilterProcessor.hpp
 * @brief processes one Filter (standalone app).
 * @author Nicolas Silva (email: nical.silva@gmail.com  twitter: @nicalsilva)
 */

#include "SimpleFilterProcessor.hpp"
#include "ArgumentProcessor.hpp"
#include "kiwi/text/PlainTextLine.hpp"
#include "kiwi/text/TextToMorseFilter.hpp"
#include "kiwi/core/DataPort.hpp"
#include "kiwi/core/ReaderPort.hpp"
#include "kiwi/core/WriterPort.hpp"

#include "kiwi/core.hpp" 
#include "kiwi/text.hpp" 

#include <iostream>
#include <fstream>


using namespace std;

namespace kiwi{
namespace app{


SimpleFilterProcessor::SimpleFilterProcessor( const ArgumentProcessor& arguments )
  : arguments(arguments)
{

}

int SimpleFilterProcessor::run()
{
  ScopedBlockMacro(__scop, "SimpleFilterProcessor::run")	
  kiwi::utils::NodeFactory factory;
  kiwi::text::UpperCaseFilter::registerToFactory(factory,"UpperCase");
  kiwi::text::TextToMorseFilter::registerToFactory(factory,"MorseCode");


  //Filter instanciation
  kiwi::core::Node* F = factory.newObject(arguments.filterName() );
  if (!F)
  {
	typedef kiwi::utils::NodeFactory NodeFactory;  
	cout << "ERROR : Could not find this filter." << std::endl
		<< "The available filters are:" << std::endl;
	NodeFactory::ClassList available =  factory.availableClasses();
	for(NodeFactory::ClassList::iterator it = available.begin()
			; it != available.end()
			; ++it )
		cout << "  * " << it->first << std::endl;
	return 1;
  }
 
  std::list<kiwi::string> inputArgs = arguments.getFilterInputs();
  std::list<kiwi::string> outputArgs = arguments.getFilterOutputs();


  wrapInputs(factory, *F, inputArgs );

  typedef std::list<std::pair<kiwi::core::Node*,std::string> > OutNodeList;
  
  OutNodeList outputNodes = wrapOutputs(factory, *F, outputArgs );


  // run the filter
  assert( F->isReady() );
  F->update();

  
  for(OutNodeList::iterator it = outputNodes.begin(); it != outputNodes.end();++it){
    if(it->second == std::string("-cout") ){
      kiwi::text::PlainTextContainer* container
        = it->first->dataPort(0).safeDownCastContainer<kiwi::text::PlainTextContainer>();
      assert(container);
      for(int i = 0; i < container->nbLines(); ++i){
        std::cout << container->line(i).str() << "\n";
      }
    }else{
      Debug::error() << " saving result into files not implemented yet \n";
    }
  }
  
  return 0;

}



void SimpleFilterProcessor::wrapInputs(
	utils::NodeFactory& factory
	, core::Node& filter
	, std::list<string>& inputs )
{
	ScopedBlockMacro(scop, "SimpleFilterProcessor::wrapInputs");

	typedef std::list<string> ArgList;

  //DEBUG
    Debug::print() << "-- The selected filter has " << (int)filter.nbReaderPorts() << " reader ports\n";
    Debug::print() << "-- Versus " << (int)inputs.size() << " input arguments\n";
  //DEBUG

	for( int i = 0; i < filter.nbReaderPorts(); ++i )
	{
    ScopedBlockMacro(forscop,
      std::string("for(") + boost::lexical_cast<std::string>(i) + std::string(")") )
    kiwi::string inputArgument("cout");
		if(i < inputs.size() ) inputArgument = inputs.front();

    bool tryFile = false;
		std::ifstream* file;
		
    file = new std::ifstream(inputArgument.c_str() );

		if( inputArgument == kiwi::string("-x") ) 
		{
      ScopedBlockMacro(forscopx, "-x")
			if(inputs.size() > 0) inputs.pop_front();
			// ignore argument and make no connections for the 
			// corresponding input portDebug::print() << "-- params --\n";
			continue;
		}
		else if( file->is_open() ) 
		{
      ScopedBlockMacro(forscopfile, "file")
			kiwi::text::PlainTextContainer* inputText
				= new kiwi::text::PlainTextContainer;
			inputText->init(*file);
			file->close();
			kiwi::core::Node* inputTextNode = new kiwi::core::Node( inputText );
			inputTextNode->dataPort(0) >> filter.readerPort(i);
			inputs.pop_front();
      assert( filter.readerPort(i).isConnected() );
		}else{
      ScopedBlockMacro(forscopplop, "input arg or cin")
			//Creation of a basic container, needed to apply the filter
			kiwi::text::PlainTextContainer* basicInputContainer
				= new kiwi::text::PlainTextContainer;
        
      Debug::plop();
      if(inputs.size() > 0) inputs.pop_front();
      Debug::plop();
      
      if((inputArgument == kiwi::string("cin")) 
			  || (inputArgument == kiwi::string("--")) )
			{
         Debug::foo();
				basicInputContainer->init(std::cin);
			}
			else
			{
        Debug::bar();
        basicInputContainer->insertLine(
					kiwi::text::PlainTextLine( inputArgument ), 0 );			 
			}
      Debug::plop();
			//Connexion between the input container and the filter, then apply filter	
			kiwi::core::Node* basicInputNode = new kiwi::core::Node(basicInputContainer);
			basicInputNode->dataPort(0) >> filter.readerPort(i);
			if(!filter.readerPort(0).isConnected() ) 
			std::cerr << "connection error"<<std::endl;
		}
		if( file->is_open() ) file->close();
		delete file;
	}
}





std::list< std::pair<kiwi::core::Node*,std::string> > SimpleFilterProcessor::wrapOutputs(
	utils::NodeFactory& factory
	, core::Node& filter
	, std::list<string>& outputs )
{
	ScopedBlockMacro(scop, "SimpleFilterProcessor::wrapOutputs");
	typedef std::list<string> ArgList;
  typedef std::list< std::pair<kiwi::core::Node*,std::string> > OutputNodeList;
  //DEBUG
    Debug::print() << "-- The selected filter has " << (int)filter.nbWriterPorts() << " writer ports\n";
    Debug::print() << "-- Versus " << (int)outputs.size() << " output arguments\n";
  //DEBUG

  OutputNodeList outputList;
	int nbParams = filter.nbWriterPorts();
	
  // for each argument
	for( int i = 0; i < nbParams ; ++i )
	{
    ScopedBlockMacro(forscop, "for...");
    
		kiwi::string inputArgument = "cout";
		if( i < outputs.size() )kiwi::string inputArgument = outputs.front();

    Debug::foo();
    
		if( inputArgument == kiwi::string("-x") ) 
		{
      ScopedBlockMacro(forscopx, "-x")
			outputs.pop_front();
			// ignore argument and make no connections for the 
			// corresponding input port
			continue;

		}else{
      ScopedBlockMacro(forscopany, "any argument")
			//Creation of a basic container, needed to apply the filter
			kiwi::text::PlainTextContainer* basicInputContainer
				= new kiwi::text::PlainTextContainer;
      Debug::bar();
			if( outputs.size() > 0 )outputs.pop_front();
      Debug::bar();
			//Connexion between the input container and the filter, then apply filter	
			kiwi::core::Node* basicInputNode = new kiwi::core::Node(basicInputContainer);
			basicInputNode->dataPort(0) >> filter.writerPort(i);

      assert( filter.writerPort(0).isConnected() );

      if((inputArgument == kiwi::string("cout"))
			  || (inputArgument == kiwi::string("--")) ){
        outputList.push_front( std::pair<kiwi::core::Node*,std::string>(basicInputNode, "-cout" ) );
      }else{
        outputList.push_front( std::pair<kiwi::core::Node*,std::string>(basicInputNode,inputArgument) );
      }
		}
	}
  return outputList;
}


}//namespace
}//namespace


