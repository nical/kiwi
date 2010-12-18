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

        int arg1 = resolveSelectFirstArgument(serverSocket1,serverSocket2,serverSocket3,serverSocket4,serverSocket5);
        if (select(arg1,&socketsGroup,NULL,NULL,&pollingSleepTime)) //If there's any data
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
    }
  }


  /**
   * Calculate the first agument of the SELECT function.
   *
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
  void * TelnetServer::startTelnetTerminal(void * dataSocket)
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


}//namespace
