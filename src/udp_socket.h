// based on ruby's udpsocket class
#ifndef UPD_SOCKET_H
#define UPD_SOCKET_H
#include <string>
class UDPSocket
{
public:
  UDPSocket(int ai_family) {};
  virtual ~UDPSocket();

  // returns if the bind was successful
  virtual bool Bind(std::string, std::string);

  //int maxlen, int flags, struct sockaddr *sender_inet_addr
  // returns received content
  virtual std::string RecvfromNonblock(int maxlen, int flags, struct sockaddr *sender_inet_addr);
  // returns number of bytes sent
  virtual int Send(std::string mesg, int flags);
private:
  /* data */
};
#endif
