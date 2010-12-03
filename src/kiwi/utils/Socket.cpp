#include "Socket.hpp"

#define UCP SOCK_DGRAM
#define TCP SOCK_STREAM

namespace kiwi
{
namespace utils
{

/**
 * Internal method of socket creation.
 *
 * @param type UDP/TCP
 * @param port Connection port 
 */
int Socket::genericSocket(int type, int port)
{
  int socketDescriptor;
  int sockaddrLentgh=sizeof(struct sockaddr_in);
  struct sockaddr_in socketAddress;
  
  try
  {
    if ((socketDescriptor=socket(AF_INET,type,0)) == -1)
      throw ios_base::failure("Could not create socket");
    socketAddress.sin_family=AF_INET; //Internet address
    socketAddress.sin_addr.s_addr=htonl(INADDR_ANY); //Listen on all network interfaces
    socketAddress.sin_port=htons(port); //Changing Endian code
    if (bind(socketDescriptor,(struct sockaddr*)&socketAddress,longueur) == -1)
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
int Socket::udpSocket();
{
  return genericSocket(UCP,0);
}


/**
 * Create a udp server socket.
 */
int Socket::udpServerSocket(int port)
{
  return genericSocket(UDP,port);
}


/**
 * Create a tcp client socket.
 */
int Socket::tcpSocket();
{
  return genericSocket(TCP,0);
}


/**
 * Create a tcp server socket.
 */
int Socket::tcpServerSocket(int port, int backlog);
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
