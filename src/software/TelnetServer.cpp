#include "TelnetServer.hpp"

using namespace std;

namespace kiwi
{

  /**
   * Constructor, Initialize service sockets and SELECT loop.
   */
  TelnetServer::TelnetServer(int port)
  {
    {
      kiwi::utils::SocketCreator sc;
      _serverSocket1 = sc.tcpServerSocket(port);
      _serverSocket2 = sc.tcpServerSocket(port+1);
      _serverSocket3 = sc.tcpServerSocket(port+2);
      _serverSocket4 = sc.tcpServerSocket(port+3);
      _serverSocket5 = sc.tcpServerSocket(port+4);

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
        FD_SET(_serverSocket1,&socketsGroup);
        FD_SET(_serverSocket2,&socketsGroup);
        FD_SET(_serverSocket3,&socketsGroup);
        FD_SET(_serverSocket4,&socketsGroup);
        FD_SET(_serverSocket5,&socketsGroup);
        pollingSleepTime.tv_sec=0;
        pollingSleepTime.tv_usec=1000;

        int arg1 = resolveSelectFirstArgument(_serverSocket1,_serverSocket2,_serverSocket3,_serverSocket4,_serverSocket5);
        if (select(arg1,&socketsGroup,NULL,NULL,&pollingSleepTime)) //If there's any data
        {
          if (FD_ISSET(_serverSocket1,&socketsGroup))
          {
            int socket=accept(_serverSocket1,(struct sockaddr*)&tcp_addr,&(tcp_size));
            if (socket==-1)
            {
              cerr << "Could not connect to an incoming client." << endl;
            }
            else
            {
              pthread_t th;
              struct threadArgStruct params;
              params.objectPtr=this;
              params.dataSocket=socket;
              pthread_create(&th,NULL,threadFunction,(void*)&params );
              pthread_detach(th);
            }
          }
          if (FD_ISSET(_serverSocket2,&socketsGroup))
          {
            int socket=accept(_serverSocket2,(struct sockaddr*)&tcp_addr,&(tcp_size));
            if (socket==-1)
            {
              cerr << "Could not connect to an incoming client." << endl;
            }
            else
            {
              pthread_t th;
              struct threadArgStruct params;
              params.objectPtr=this;
              params.dataSocket=socket;
              pthread_create(&th,NULL,threadFunction,(void *)&params);
              pthread_detach(th);
            }
          }
          if (FD_ISSET(_serverSocket3,&socketsGroup))
          {
            int socket=accept(_serverSocket3,(struct sockaddr*)&tcp_addr,&(tcp_size));
            if (socket==-1)
            {
              cerr << "Could not connect to an incoming client." << endl;
            }
            else
            {
              pthread_t th;
              struct threadArgStruct params;
              params.objectPtr=this;
              params.dataSocket=socket;
              pthread_create(&th,NULL,threadFunction,(void *)&params);
              pthread_detach(th);
            }
          }
          if (FD_ISSET(_serverSocket4,&socketsGroup))
          {
            int socket=accept(_serverSocket4,(struct sockaddr*)&tcp_addr,&(tcp_size));
            if (socket==-1)
            {
              cerr << "Could not connect to an incoming client." << endl;
            }
            else
            {
              pthread_t th;
              struct threadArgStruct params;
              params.objectPtr=this;
              params.dataSocket=socket;
              pthread_create(&th,NULL,threadFunction,(void *)&params);
              pthread_detach(th);
            }
          }
          if (FD_ISSET(_serverSocket5,&socketsGroup))
          {
            int socket=accept(_serverSocket5,(struct sockaddr*)&tcp_addr,&(tcp_size));
            if (socket==-1)
            {
              cerr << "Could not connect to an incoming client." << endl;
            }
            else
            {
              pthread_t th;
              struct threadArgStruct params;
              params.objectPtr=this;
              params.dataSocket=socket;
              pthread_create(&th,NULL,threadFunction,(void *)&params);
              pthread_detach(th);
            }
          }
        }
      }
    }
  }


  /**
   * Calculate the first agument of the SELECT function.
   * @param Service sockets.
   */
  int TelnetServer::resolveSelectFirstArgument(int n1, int n2, int n3, int n4, int n5)
  {
    int retval = n1;
    if (n2>retval) retval=n2;
    if (n3>retval) retval=n3;
    if (n4>retval) retval=n4;
    if (n5>retval) retval=n5;
    return retval;
  }


  /**
   * Start a new thread for an interactive terminal with a client.
   * Close the data socket once terminated.
   */
  void * TelnetServer::threadFunction(void * threadArg)
  {
    struct threadArgStruct * params = (struct threadArgStruct *)threadArg;
    TelnetServer* obj = (TelnetServer*) params->objectPtr;
    int dataSocket = (int) params->dataSocket;
    obj->startTelnetTerminal(dataSocket);
  }

  void TelnetServer::startTelnetTerminal(int dataSocket)
  {
    int socket = (int) dataSocket;
    bool go = true;
    kiwi::TelnetRequestParser * myParser = new kiwi::TelnetRequestParser();

    while ( myParser->oneMoreLoop() )
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

      outputBuffer=myParser->reply(inputBuffer);
      write(socket,outputBuffer.c_str(),outputBuffer.size());
    }
    
    //Don't be dirty.
    delete(myParser);
    close(socket);
  }
}//namespace
