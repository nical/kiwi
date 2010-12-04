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
#include "kiwi/core/Commons.hpp"
#include "kiwi/core/NodeFactory.hpp"
#include "kiwi/core/Filter.hpp"
#include "kiwi/text/TextContainer.hpp"
#include "kiwi/text/TextReader.hpp"
#include "kiwi/text/TextWriter.hpp"
#include "kiwi/text/UpperCaseFilter.hpp"
#include "kiwi/utils/Socket.hpp"
#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;



/**
 * Print version on standard outpur.
 */
void printVersion()
{
  cout << "Kiwi version : " << KIWI_VERSION_MAJOR << "." << KIWI_VERSION_MINOR 	<< "." << KIWI_VERSION_PATCH << endl;
}



/**
 * Print help text on standard output.
 */
void printHelp()
{
  cout << endl;

  cout << "Synopsis:" << endl << endl;
  cout << "     kiwi [--help] [--version] [filterName [-i inputs] [-o outputs]]" << endl;
  cout << endl << "Description:" << endl << endl;
  cout << "     @TODO" << endl;
  cout << endl << "Options:" << endl << endl;
  cout << "     --help" << endl;
  cout << "        Shows this output" << endl;
  cout << "     --version"  << endl;
  cout << "        Prints the installed kiwi version. " << endl;
  cout << "     -i" << endl;
  cout << "        Followed by the input arguments." << endl;
  cout << "     -o " << endl;
  cout << "        Followed by the output arguments." << endl;
  cout << endl << endl;
}




/**
 * Main loop.
 */
int main(int argc, char *argv[])
{

  //DEBUG ON
  kiwi::Debug::init(true, true, 0);
  

  //BEGIN : Register all nodes.
  kiwi::core::NodeFactory factory;
  kiwi::text::UpperCaseFilter::registerToFactory(factory,"UpperCaseFilter");
  //END: Register all nodes.



  //BEGIN : SERVER REQUEST CASE.
  if(argc==3)
  {
    if (kiwi::string(argv[1])==kiwi::string("--server"))
    {
      while (1);
    }
  }
  //END : SERVER REQUEST CASE.



  //BEGIN : ONE ARGUMENT CASE. It should be a "help" or a "version" request.
	if(argc==2)
	{
		if(kiwi::string(argv[1]) == kiwi::string("--version") )
		{
      printVersion();
			return 0;
		}
		else if (kiwi::string(argv[1]) == kiwi::string("--help") )
		{
      printHelp();
      return 0; 
		}
		else
		{
      printHelp();
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
      printHelp();
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
    kiwi::core::Filter* F = factory.newFilter(filterName);
    if (!F)
    {
      cout << "SYNTAX ERROR : Could not finf this filter. Please check help" << endl;
      printHelp();
      return 1;
    }
    //END : Filter instanciation using filter name extracted from arguments
    printf("DEBUG\n");



    //Creation of a basic container, needed to apply the filter
    kiwi::text::TextContainer basicInputContainer;

    //Creation of a Writer needed to write the argument in the container
    kiwi::text::TextWriter writer(basicInputContainer,0);
    writer.getLine() = inputList.at(0); //TODO Change!

    //Connexion between the input container and the filter, then apply filter
    basicInputContainer.readerOutputPort(0) >> F->readerInputPort(0);
    F->process();

    //Creation of a Reader needed to read text from a node
    kiwi::text::TextReader reader( F->readerOutputPort(0) );
    cout << reader.getLine() << endl;

  }
  //END : Filter use request.
		
}

