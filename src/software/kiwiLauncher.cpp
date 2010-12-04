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
  kiwi::Debug::init(true, true, 0);


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
  

  
  //BEGIN : TWO ARGUMENTS CASE.
  if(argc==3)
  {
    if (kiwi::string(argv[1])==kiwi::string("--server"))
    {
      while (1);
    }
  }
  //END : TWO ARGUMENTS CASE.



  //BEGIN : Filter use request.
  else if (argc>2)
  {
    //BEGIN : Find inputs and outputs arguments indexes.
    int inputsIndex=0;
    int outputsIndex=0;
    for (int i=1;i<argc;i++)
    {
      if (argv[i]=="-i") inputsIndex=i;
      else if (argv[i]=="-o") outputsIndex=i;
    }

    if (
        (inputsIndex<2) ||
        (outputsIndex<2) ||
        (inputsIndex>argc-2) ||
        (inputsIndex==argc-1) ||
        (outputsIndex-inputsIndex<2)
       )
    {
      cout << "SYNTAX ERROR : Please check help" << endl;
      printHelp();
      return 1;
    }
    //END : Find inputs and outputs arguments indexes.


    //BEGIN : Register all nodes.
    kiwi::core::NodeFactory factory;
    kiwi::text::UpperCaseFilter::registerToFactory(factory,"UpperCaseFilter");
    //END: Register all nodes.

    
    //Filter instanciation using filter name extracted from arguments
    kiwi::core::Filter* F = factory.newFilter(argv[inputsIndex-1]);
    if (!F)
    {
      cout << "SYNTAX ERROR : Please check help" << endl;
      printHelp();
      return 1;
    }

    //Creation of a basic container, needed to apply the filter
    kiwi::text::TextContainer basicInputContainer;

    //Creation of a Writer needed to write the argument in the container
    kiwi::text::TextWriter writer(basicInputContainer,0);
    writer.getLine() = kiwi::string(argv[inputsIndex+1]); //TODO Change!

    //Connexion between the input container and the filter.
    basicInputContainer.readerOutputPort(0) >> F->readerInputPort(0);

    //Apply filter
    F->process();

    //Creation of a Reader needed to read text from a node
    kiwi::text::TextReader reader( F->readerOutputPort(0) );
    cout << reader.getLine() << endl;

  }
  //&END : Filter use request.
		

  //BEGIN : Syntax error.
	else
	{
		cout << "SYNTAX ERROR : Please specify comandline arguments" << endl;
    printHelp();
		return 1;
	}
  //END : Syntax error.
	
}

