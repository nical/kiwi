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
 * @author Nicolas Silva (email: nical.silva@gmail.com  twitter: @nicalsilva) * @version 0.1
 */

#include "SimpleFilterProcessor.hpp"
#include "ArgumentProcessor.hpp"

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
      kiwi::core::NodeFactory factory;
      kiwi::text::UpperCaseFilter::registerToFactory(factory,"UpperCaseFilter");


      //Filter instanciation
      kiwi::core::Filter* F = factory.newFilter(arguments.filterName() );
      if (!F)
      {
        cout << "SYNTAX ERROR : Could not find this filter. Please check help" << endl;
        return 1;
      }
      //cout << "Inputs number : " << arguments.getFilterInputs().size() << endl;
      //cout << "Outputs number : " << arguments.getFilterOutputs().size() << endl;


      std::list<kiwi::string> inputArgs = arguments.getFilterInputs();

      wrapInputs(factory, *F, inputArgs );

      // run the filter
      if( F->isReady() ) F->process(); 

      //Creation of a Reader needed to read text from a node
      if(F->readerOutputPort(0).isEnabled() )
      {
        kiwi::text::TextReader reader( F->readerOutputPort(0) );
        reader.gotoLine(0);
        do
        { 
          cout << reader.getLine() << std::endl;
          reader.gotoNextLine();
        } while(reader.currentLine() != reader.nbLines()-1 );
      }
      //END : Filter use request.

      return 0;

    }



    void SimpleFilterProcessor::wrapInputs(core::NodeFactory& factory, core::Filter& filter, std::list<string>& inputs)
    {

      typedef std::list<string> ArgList;
      ArgList::iterator it = inputs.begin();
      ArgList::iterator itEnd = inputs.end();
      int nbParams = inputs.size();
      if(nbParams > filter.nbReaderInputs()) nbParams = filter.nbReaderInputs();

      for(int i = 0; i < nbParams ; ++i, ++it)
      {	
        std::ifstream file(it->c_str() );
        kiwi::string inputArgument = inputs.front();
        if( inputArgument == kiwi::string("-x") ) 
        {
          // ignore argument and make no connection for the 
          // corresponding input port
          continue;
        }
        else if( file.is_open() ) 
        {	
          kiwi::text::TextContainer* inputText = new kiwi::text::TextContainer;



          inputText->init(file);
          file.close();
          inputText->readerOutputPort(0) >> filter.readerInputPort(i);

        }else{

          //Creation of a basic container, needed to apply the filter
          kiwi::text::TextContainer* basicInputContainer = new kiwi::text::TextContainer;


          inputs.pop_front();
          if((inputArgument == kiwi::string("cin")) 
              || (inputArgument == kiwi::string("--")) )
          {
            basicInputContainer->init(std::cin);
          }
          else
          {
            //Creation of a Writer needed to write the argument in the container
            kiwi::text::TextWriter writer(*basicInputContainer,0);
            writer.getLine() = inputArgument;
          }
          //Connexion between the input container and the filter, then apply filter
          basicInputContainer->readerOutputPort(0) >> filter.readerInputPort(i);
          if(!filter.readerInputPort(0).isConnected() ) 
            std::cerr << "connection error"<<std::endl;
        }
      }

    }


  }//namespaces
}//namespace
