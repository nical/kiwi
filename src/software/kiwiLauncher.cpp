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
#include "InputWrapper.hpp"

#include "Help.hpp"

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>

using namespace std;



/**
 * Return the first argument of the select function
 */
int selectFirstArgument(int n1, int n2, int n3, int n4, int n5)
{
  int retval = n1;
  if (n2>retval) retval=n2;
  if (n3>retval) retval=n3;
  if (n4>retval) retval=n4;
  if (n5>retval) retval=n5;
  return retval;
}



/**
 * Start interactive terminal on a data socket.
 */
static void * startTelnetTerminal(void * dataSocket)
{
  int socket = (int) dataSocket;
  bool go = true;
  while (go)
  {
    kiwi::string outputBuffer;
    kiwi::string inputBuffer;
    outputBuffer = "kiwi : remote --> ";
    if ((write(socket,outputBuffer.c_str(),outputBuffer.size()))==-1)
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
      write(socket,outputBuffer.c_str(),outputBuffer.size());
    }
    else if ((inputBuffer=="quit")||(inputBuffer=="exit"))
    {
      go=false;
    }
    else if (inputBuffer!="")
    {
      outputBuffer = "You've just written \"" + inputBuffer +"\". Happy, rn't u ?\r\n"; 
      write(socket,outputBuffer.c_str(),outputBuffer.size());
    }
    //END : Request analysis

  }
  //END : Start interactive terminal
  close(socket);
  return 0;
}



/**
 * Launch TCP server.
 */
int launchServer(int port)
{
  //Setting up service socket
  kiwi::utils::SocketCreator sc;
  int serverSocket1 = sc.tcpServerSocket(port);
  int serverSocket2 = sc.tcpServerSocket(port+1);
  int serverSocket3 = sc.tcpServerSocket(port+2);
  int serverSocket4 = sc.tcpServerSocket(port+3);
  int serverSocket5 = sc.tcpServerSocket(port+4);

  //Declaring some variables
  struct sockaddr_in tcp_addr;
  unsigned int tcp_size = sizeof(tcp_addr);
  fd_set socketsGroup;
  struct timeval pollingSleepTime;

  while(1)
  {
    /**
     * Using SELECT Function.
     *
     * Listenning on all sockets at the same time. Queue requests.
     * Time value is specified by variable pollingSleepTime.
     *
     * If you don't understand, RTFM.
     */
    FD_ZERO(&socketsGroup);
    FD_SET(serverSocket1,&socketsGroup);
    FD_SET(serverSocket2,&socketsGroup);
    FD_SET(serverSocket3,&socketsGroup);
    FD_SET(serverSocket4,&socketsGroup);
    FD_SET(serverSocket5,&socketsGroup);
    pollingSleepTime.tv_sec=0;
    pollingSleepTime.tv_usec=1000;

    int selfarg = selectFirstArgument(serverSocket1,serverSocket2,serverSocket3,serverSocket4,serverSocket5);
    if (select(selfarg,&socketsGroup,NULL,NULL,&pollingSleepTime)) //If there's any data
    {
      if (FD_ISSET(serverSocket1,&socketsGroup))
      {
        int socket=accept(serverSocket1,(struct sockaddr*)&tcp_addr,&(tcp_size));
        if (socket==-1)
        {
          cerr << "Could not connect to an incoming client." << endl;
        }
        else
        {
          pthread_t th;
          pthread_create(&th,NULL,startTelnetTerminal,(void *)socket);
          pthread_detach(th);
        }
      }
      if (FD_ISSET(serverSocket2,&socketsGroup))
      {
        int socket=accept(serverSocket2,(struct sockaddr*)&tcp_addr,&(tcp_size));
        if (socket==-1)
        {
          cerr << "Could not connect to an incoming client." << endl;
        }
        else
        {
          pthread_t th;
          pthread_create(&th,NULL,startTelnetTerminal,(void *)socket);
          pthread_detach(th);
        }
      }
      if (FD_ISSET(serverSocket3,&socketsGroup))
      {
        int socket=accept(serverSocket3,(struct sockaddr*)&tcp_addr,&(tcp_size));
        if (socket==-1)
        {
          cerr << "Could not connect to an incoming client." << endl;
        }
        else
        {
          pthread_t th;
          pthread_create(&th,NULL,startTelnetTerminal,(void *)socket);
          pthread_detach(th);
        }
      }
      if (FD_ISSET(serverSocket4,&socketsGroup))
      {
        int socket=accept(serverSocket4,(struct sockaddr*)&tcp_addr,&(tcp_size));
        if (socket==-1)
        {
          cerr << "Could not connect to an incoming client." << endl;
        }
        else
        {
          pthread_t th;
          pthread_create(&th,NULL,startTelnetTerminal,(void *)socket);
          pthread_detach(th);
        }
      }
      if (FD_ISSET(serverSocket5,&socketsGroup))
      {
        int socket=accept(serverSocket5,(struct sockaddr*)&tcp_addr,&(tcp_size));
        if (socket==-1)
        {
          cerr << "Could not connect to an incoming client." << endl;
        }
        else
        {
          pthread_t th;
          pthread_create(&th,NULL,startTelnetTerminal,(void *)socket);
          pthread_detach(th);
        }
      }
    }
  }
  return 0;
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

