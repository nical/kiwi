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
 * @file kiwiLauncher.hpp
 * @brief Commandline kiwi program.
 * @author Semprobe aka Thibaut Vuillemin (mail: contact@thibautvuillemin.com twitter: @Semprobe)
 * @version 0.1
 */
#include "kiwi/core.hpp"
#include "kiwi/text.hpp"

#include "kiwi/utils/Socket.hpp"

#include "ArgumentProcessor.hpp"
#include "InputWrapper.hpp"

#include "Help.hpp"

#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;




/**
 * Main loop.
 */
int main(int argc, char *argv[])
{

  //DEBUG ON
  kiwi::Debug::init(true, true, 0);
  
  kiwi::ArgumentProcessor arguments(argc, argv);

  //BEGIN : Register all nodes.
  kiwi::core::NodeFactory factory;
  kiwi::text::UpperCaseFilter::registerToFactory(factory,"UpperCaseFilter");
  //END: Register all nodes.

	if( arguments.invalid() ) 
	{
		cerr << "SYNTAX ERROR"<<endl;
		kiwi::Help::print(cerr);
		return 1;
	}
	
	if( arguments.helpCmd() )
	{
		kiwi::Help::print(cout);
		return 1;
	}
	
	//BEGIN : SERVER REQUEST CASE.
	if( arguments.serverCmd() )
	{
      cerr << "kiwi server not supported yet" << endl;
      return 1;
    } //END : SERVER REQUEST CASE.

	
	if( arguments.processCmd() ) cout << "process " << endl;
	if( arguments.versionCmd() ) cout << "version " << endl;
	if( arguments.verboseCmd() ) cout << "verbose " << endl;
	if( arguments.helpCmd() ) cout << "help " << endl;
	if( arguments.remoteCmd() ) cout << "remote " << endl;
	if( arguments.serverCmd() ) cout << "server " << endl;
	cout << "nb inputs " << arguments.getFilterInputs().size() << endl;
	cout << "nb outputs " << arguments.getFilterOutputs().size() << endl;
	return 0;
 /*



  //BEGIN : ONE ARGUMENT CASE. It should be a "help" or a "version" request.
	if(argc==2)
	{
		if(kiwi::string(argv[1]) == kiwi::string("--version") )
		{
			kiwi::Help::printVersion(cout);
			return 0;
		}
		else if (kiwi::string(argv[1]) == kiwi::string("--help") )
		{
			kiwi::Help::print(cout);
			return 0; 
		}
		else
		{
			kiwi::Help::print(cout);
			return 1; 
		}
	}
  //END : ONE ARGUMENT CASE.
  

  
  //BEGIN : Filter use request.
  else
  {

    //BEGIN : Getting arguments
    int i;
    int verbose=0;
    std::vector<kiwi::string> inputList;
    std::vector<kiwi::string> outputList;
    if (strcmp(argv[1],"-v")==0) verbose=1;
    kiwi::string filterName(argv[verbose+1]);
    if (strcmp(argv[verbose+2],"-i")!=0)
    {
      cout << "SYNTAX ERROR : Could not fint input list symbol. Please check help" << endl;
      kiwi::Help::print(cout);
      return 1;
    }
    i=verbose+3;
    while ((i!=argc)&&((strcmp(argv[i],"-o"))!=0))
    {
      inputList.push_back(kiwi::string(argv[i++]));
    }
    while (i!=argc)
    {
      outputList.push_back(kiwi::string(argv[i++]));
    }
    //END: Getting arguments



    //BEGIN : Filter instanciation using filter name extracted from arguments
   
    //END : Filter instanciation using filter name extracted from arguments
    printf("DEBUG\n");

*/

	if( arguments.processCmd() )
	{
		kiwi::core::Filter* F = factory.newFilter(arguments.filterName() );
		if (!F)
		{
		  cout << "SYNTAX ERROR : Could not finf this filter. Please check help" << endl;
		  kiwi::Help::print(cout);
		  return 1;
		}

		//Creation of a basic container, needed to apply the filter
		kiwi::text::TextContainer basicInputContainer;

		//Creation of a Writer needed to write the argument in the container
		kiwi::text::TextWriter writer(basicInputContainer,0);
		writer.getLine() = arguments.getFilterInputs().front();

		//Connexion between the input container and the filter, then apply filter
		basicInputContainer.readerOutputPort(0) >> F->readerInputPort(0);
		F->process();

		//Creation of a Reader needed to read text from a node
		kiwi::text::TextReader reader( F->readerOutputPort(0) );
		cout << reader.getLine() << endl;

  }
  //END : Filter use request.
		
}

