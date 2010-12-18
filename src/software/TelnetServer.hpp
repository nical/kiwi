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
 * @file kiwiServer.cpp
 * @brief Handle clients connections.
 * @author Semprobe aka Thibaut Vuillemin (mail: contact@thibautvuillemin.com twitter: @Semprobe)
 */

#ifndef KIWI_TELNETSERVER_HPP
#define KIWI_TELNETSERVER_HPP

#include "kiwi/core.hpp"
#include "kiwi/utils/SocketCreator.hpp"
#include "TelnetRequestParser.hpp"
#include <iostream>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>

namespace kiwi
{

  /**
   * This class handles client connections.
   *
   * It starts a new thread for each new client.
   * Clients maximum number is 5.
   */ 
  class TelnetServer
  {
    public:
      TelnetServer(int port);

    private:
      int resolveSelectFirstArgument(int n1, int n2, int n3, int n4, int n5);
      static void * threadFunction(void * threadArg);
      void startTelnetTerminal(int dataSocket);

      int _serverSocket1;
      int _serverSocket2;
      int _serverSocket3;
      int _serverSocket4;
      int _serverSocket5;
  };


  /**
   * Structure used to pass arguments to the threadFunction.
   */
  struct threadArgStruct
  {
    TelnetServer * objectPtr;
    int dataSocket;
  };

}// namespace
#endif //KIWI_TELNETSERVER_HPP
