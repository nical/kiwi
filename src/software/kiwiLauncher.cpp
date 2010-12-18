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
 * @file kiwiLauncher.cpp
 * @brief Commandline kiwi program.
 * @author Semprobe aka Thibaut Vuillemin (mail: contact@thibautvuillemin.com twitter: @Semprobe)
 * @version 0.1
 */

#include "kiwi/core.hpp"
#include "kiwi/text.hpp"
#include "kiwi/utils/SocketCreator.hpp"
#include "ArgumentProcessor.hpp"
#include "InputWrapper.hpp"
#include "TelnetServer.cpp"

#include "Help.hpp"

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;


/**
 * Main loop.
 */
int main(int argc, char *argv[])
{

  //Initialization
  kiwi::Debug::init(true, true, 0);
  kiwi::ArgumentProcessor arguments(argc, argv);
  kiwi::core::NodeFactory factory;
  kiwi::text::UpperCaseFilter::registerToFactory(factory,"UpperCaseFilter");


  //Invalid syntax
  if( arguments.invalid() ) 
  {
    cerr << "SYNTAX ERROR"<<endl;
    kiwi::Help::print(cerr);
    return 1;
  }


  //Help request
  if( arguments.helpCmd() )
  {
    kiwi::Help::print(cout);
    return 0;
  }


  //Version request
  if( arguments.versionCmd() )
  {
    cout << "Kiwi version : ???" << endl;
    return 0;
  }


  //Server request
  if( arguments.serverCmd() )
  {
    int port = arguments.getServerPort();
    cout << "Starting kiwi server on port " << port << "..." << endl;
    kiwi::TelnetServer ts(port);
  }


  //Remote request
  if( arguments.remoteCmd() )
  {
    cerr << "Kiwi remote mode not supported yet" << endl;
    return 0;
  }


  //Verbose request
  if( arguments.verboseCmd() )
  {
    cerr << "Kiwi verbose mode not supported yet" << endl;
    return 0;
  }


  //Process request
  if( arguments.processCmd() )
  {

    //Filter instanciation
    kiwi::core::Filter* F = factory.newFilter(arguments.filterName() );
    if (!F)
    {
      cout << "SYNTAX ERROR : Could not find this filter. Please check help" << endl;
      kiwi::Help::print(cout);
      return 1;
    }

    std::list<kiwi::string> inputArgs = arguments.getFilterInputs();

    kiwi::wrapInputs(factory, *F, inputArgs );

    // run the filter
    F->process();

    //Creation of a Reader needed to read text from a node
    kiwi::text::TextReader reader( F->readerOutputPort(0) );
    reader.gotoLine(0);
    do
    { 
      cout << reader.getLine() << endl;
      reader.gotoNextLine();
    } while(reader.currentLine() != reader.nbLines()-1 );
  }
  //END : Filter use request.
}

