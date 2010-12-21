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
 * @version 0.5
 */

#include "kiwi/core.hpp"
#include "ArgumentProcessor.hpp"
#include "SimpleFilterProcessor.hpp"
#include "TelnetServer.hpp"
#include "Help.hpp"
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace kiwi::app;


/**
 * Entry point of the application.
 */
int main(int argc, char *argv[])
{
  
  kiwi::Debug::init(true, true, 0);
  kiwi::app::ArgumentProcessor arguments(argc, argv);


  /**
   * Basic requests
   */
  if( arguments.invalid() ) 
  {
    cerr << "SYNTAX ERROR"<<endl;
    kiwi::Help::print(cerr);
    return 1;
  }
  if( arguments.helpCmd() )
  {
    kiwi::Help::print(cout);
    return 0;
  }
  if( arguments.versionCmd() )
  {
    cout << "Kiwi version : 0.3" << endl;
    return 0;
  }
  if( arguments.serverCmd() )
  {
    cerr << "Kiwi verbose mode not supported yet" << endl;
    return 0;
  }


  /**
   * Process request
   */
  if( arguments.processCmd() )
  {
    SimpleFilterProcessor program(arguments);
    return program.run();
  }


  /**
   * Server request
   */
  if( arguments.serverCmd() )
  {
    int port = arguments.getServerPort();
    cout << "Starting kiwi server on port " << port << "..." << endl;
    kiwi::TelnetServer ts(port);
  }
  
  return 0;
}
