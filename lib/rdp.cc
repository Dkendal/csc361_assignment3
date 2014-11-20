#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "rdp.h"
#include "util.h"

RDP::RDP(const char *ip, const char *port) : ip(ip), port(port)
{
  struct addrinfo hints = {}, *res;

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_PASSIVE;

  check(getaddrinfo(NULL, port, &hints, &res));
}
