#ifndef RDP_STATE_MACHINE_H
#define RDP_STATE_MACHINE_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "util.h"
#include "packet.h"
#include <map>

template <class T>
class RDPStateMachine
{
  public:
    RDPStateMachine(const char *ip, const char *port) : ip(ip), port(port) {
      struct addrinfo hints = {}, *res;

      hints.ai_family = AF_UNSPEC;
      hints.ai_socktype = SOCK_DGRAM;
      hints.ai_flags = AI_PASSIVE;

      check(getaddrinfo(NULL, port, &hints, &res) != 0);

      sock_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

      check(sock_fd == -1);

      int optval = 1;
      setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

      check(bind(sock_fd, res->ai_addr, res->ai_addrlen) != 0);

      freeaddrinfo(res);

      current_state = IntialState();
    }

    virtual void Process(Packet);
    virtual T IntialState();

  protected:
    T current_state;
    virtual T NextState();

    T GetState()
    {
    }

    virtual void AdvanceState();
    virtual std::map<T, T> GetStateTransitions();

  private:
    const char *ip, *port;
    int sock_fd;
};
#endif
