#ifndef RDP_LISTENER_H
#define RDP_LISTENER_H
#include "listener_state.h"

class UDPSocket;

class RDPListener
{
  public:
    RDPListener(UDPSocket *socket) : socket(socket) {};
    virtual ~RDPListener() {};

    Listener::State GetState();
    Listener::State IntialState();
    Listener::State NextState();
    void Start();

  private:
    UDPSocket *socket;
    Listener::State current_state;
};

#endif
