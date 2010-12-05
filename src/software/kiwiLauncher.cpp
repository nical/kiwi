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
#include "kiwi/utils/SocketCreator.hpp"
#include "ArgumentProcessor.hpp"
#include "Help.hpp"

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

using namespace std;


/**
 * Launch TCP server.
 */
void launchServer(int port)
{
  //Setting up service socket
  kiwi::utils::SocketCreator sc;
  int serverSocket = sc.tcpServerSocket(port);

  //Declaring some variables
  fd_set socketGroup;
  struct timeval pollingTime;
  int selectResult; 
  struct sockaddr_in tcp_addr;
  unsigned int tcp_size = sizeof(tcp_addr);
  int writeResult;

  while(1)
  {
    //BEGIN : Initialize "select" function params
    FD_ZERO(&socketGroup);
    FD_SET(serverSocket,&socketGroup);
    pollingTime.tv_sec=0;
    pollingTime.tv_usec=100;
    //END: Initialize "select" function params


    //BEGIN : Handle client connections
    selectResult=select((serverSocket+1),&socketGroup,NULL,NULL,&pollingTime);
    if (selectResult==-1)
    {
      cerr << "Error on \"select\" function.";
    }
    else
    {
      //BEGIN : IF a new client attemps to connect
      if (FD_ISSET(serverSocket,&socketGroup))
      {
        //BEGIN : New process and new socket for an incoming client
        if (fork()==0)
        {

          //BEGIN : Create new socket, buffers, display welcome message
          int socket=accept(serverSocket,(struct sockaddr*)&tcp_addr,&(tcp_size));
          if (socket==-1)
          {
            cerr << "Could not connect to an incoming client." << endl;
          }
          kiwi::string outputBuffer;
          kiwi::string inputBuffer;
          outputBuffer = "\r\n-----------------------------------------\r\n---------- Enjoy Cloud Kiwi ! -----------\r\n-----------------------------------------\r\n";
          writeResult=write(socket,outputBuffer.c_str(),outputBuffer.size());
          //END : Create new socket, buffers, display welcome message


          //BEGIN : Start interactive terminal
          bool go = true;
          while (go)
          {
            outputBuffer = "kiwi : remote --> ";
            writeResult=write(socket,outputBuffer.c_str(),outputBuffer.size());
            if (writeResult==-1)
            {
              cerr << "Could not write into an client socket." << endl;
            }

            //BEGIN : Read use request
            int eol = 0;
            char c;
            int length = 0;
            inputBuffer = "";
            /* telnet sends '1310' == '\r\n' for each newline          */
            /* eol == 2 at the end of a line after it receives '13'10' */
            while (eol < 2)
            {
              if (read(socket,&c,sizeof(char)) == -1)
              {
                cerr << "Could not read client request" << endl;
              }
              else
              {
                if (c == '\n' || c == '\r')
                {
                  eol ++;
                }
                else
                {
                  inputBuffer = inputBuffer + c;
                }
              }
            }
            //END : Read use request
            

            //BEGIN : Request analysis
            if (inputBuffer=="help")
            {
              outputBuffer = "This command should print help, don't u think so ?\r\n";
              writeResult=write(socket,outputBuffer.c_str(),outputBuffer.size());
            }
            else if (inputBuffer!="")
            {
              outputBuffer = "You've just written \"" + inputBuffer +"\". Happy, rn't u ?\r\n"; 
              writeResult=write(socket,outputBuffer.c_str(),outputBuffer.size());
            }
            //END : Request analysis

          }
          //END : Start interactive terminal
        }
        //END : New process and new socket for an incoming client
      }
      //END : IF a new client attemps to connect
    }
    //END: Handle client connections
  }
}



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
    launchServer(port);
  }


  //Remote request
  if( arguments.serverCmd() )
  {
    cerr << "Kiwi remote mode not supported yet" << endl;
    return 0;
  }


  //Verbose request
  if( arguments.serverCmd() )
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
    cout << "Inputs number : " << arguments.getFilterInputs().size() << endl;
    cout << "Outputs number : " << arguments.getFilterOutputs().size() << endl;

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

