#include "udp_socket.h"
#include <string>

UDPSocket::~UDPSocket() { }

bool UDPSocket::Bind(const char *host, int port)
{
  throw "not yet implemented";
  return false;
}

int UDPSocket::Send(const char *mesg, int flags, const char *host, int port) {
  throw "not yet implemented";
  return 0;
}
