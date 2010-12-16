#include "SocketCreator.hpp"

#define UDP SOCK_DGRAM
#define TCP SOCK_STREAM

using namespace std;

namespace kiwi{
namespace utils{

/**
 * Internal method of socket creation.
 *
 * @param type UDP/TCP
 * @param port Connection port 
 */
int SocketCreator::genericSocket(int type, int port)
{
  int socketDescriptor;
  int sockaddrLength=sizeof(struct sockaddr_in);
  struct sockaddr_in socketAddress;
  
  try
  {
    if ((socketDescriptor=socket(AF_INET,type,0)) == -1)
      throw ios_base::failure("Could not create socket");
    socketAddress.sin_family=AF_INET; //Internet address
    socketAddress.sin_addr.s_addr=htonl(INADDR_ANY); //Listen on all network interfaces
    socketAddress.sin_port=htons(port); //Changing Endian code
    if (bind(socketDescriptor,(struct sockaddr*)&socketAddress,sockaddrLength) == -1)
    {
      close(socketDescriptor);
      throw ios_base::failure("Could not attach socket");
    }
  }
  catch (const std::exception& e)
  {
    throw;
  }
  return socketDescriptor;
}



/**
 * Create a udp client socket.
 */
int SocketCreator::udpSocket()
{
  return genericSocket(UDP,0);
}


/**
 * Create a udp server socket.
 */
int SocketCreator::udpServerSocket(int port)
{
  return genericSocket(UDP,port);
}


/**
 * Create a tcp client socket.
 */
int SocketCreator::tcpSocket()
{
  return genericSocket(TCP,0);
}


/**
 * Create a tcp server socket.
 */
int SocketCreator::tcpServerSocket(int port, int backlog)
{
  int socketDescriptor = genericSocket(TCP,port);
  try
  {
    if (listen(socketDescriptor, backlog) == -1)
      throw ios_base::failure("Could not start a tcp server");
  }
  catch (const std::exception& e)
  {
    throw;
  }
  return socketDescriptor;
}

}
}
