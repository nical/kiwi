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
 * @file ArgumentProcessor.hpp
 * @brief Command-line argument processor for kiwi's standalone app.
 * @author Nicolas Silva (email: nical.silva@gmail.com  twitter: @nicalsilva)
 * @author Thibaut Vuillemin 
 */

#pragma once

#ifndef KIWI_ARGUMENTPROCESSOR_HPP
#define KIWI_ARGUMENTPROCESSOR_HPP

#include <list>
#include "kiwi/core/Commons.hpp"


namespace kiwi{
namespace app{

/**
* This class parse the arguments given to the launcher.
*
* You just have to instanciate an object of this class,
* giving argc and argv to the one constructor.
* Then you can get the informations through the getters.
*/
class ArgumentProcessor
{
public:
  enum{FALSE=0, INPUT, OUTPUT, GENERAL, PROCESS, NODE, SERVER, REMOTE};

  /**
   * Constructor.
   */
  ArgumentProcessor(int argc, char** argv);
  
  /**
   * Copy constructor.
   */ 
  ArgumentProcessor(const ArgumentProcessor&);
  
  

  /**
   * Returns the name of the called filter.
   */
  kiwi::string filterName() {return _filterName;}


  /**
   * Returns a list of the arguments following -i .
   */ 
  std::list<kiwi::string> getFilterInputs() {return _inputs;}


  /**
   * Returns a list of the arguments following -o .
   */ 
  std::list<kiwi::string> getFilterOutputs() {return _outputs;}


  /**
   * Returns true if the syntax is not correct.
   */ 
  bool invalid() {return _invalid;}


  /**
   * Returns true if the process command is invoked.
   */ 
  bool processCmd() {return _process;}


  /**
   * Returns true if the remote command is invoked.
   */ 
  bool remoteCmd() {return _remote;}


  /**
   * Returns true if the server command is invoked.
   */ 
  bool serverCmd() {return _server;}


  /**
   * Returns true if the -v command is invoked.
   */ 
  bool verboseCmd() {return _verbose;}


  /**
   * Returns a value different from 0 if the --help command is invoked.
   */ 
  int helpCmd() {return _help;}


  /**
   * Returns a value different from 0 if the --version command is invoked.
   */ 
  int versionCmd() {return _version;}


  /**
   * If kiwi was started as a server, returns the port value.
   * If not, returns 0.
   */
  int getServerPort();


private:
  bool _invalid;
  bool _verbose;
  bool _process;
  bool _server;
  bool _remote;
  int _port;
  int _version;
  int _help;
  kiwi::string _filterName;
  std::list<kiwi::string> _inputs;
  std::list<kiwi::string> _outputs;
};

}// namespace
}// namespace

#endif
