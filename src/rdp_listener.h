#ifndef SRC_RDP_LISTENER_H_
#define SRC_RDP_LISTENER_H_
#include <string>
#include "listener_state.h"

using namespace std;

class Packet;
class UDPSocket;
struct SenderInetAddr;
class RDPListener {
  public:
    RDPListener(UDPSocket *socket, const char *addr, int port);
    virtual ~RDPListener() {};

    Listener::State GetState();
    Listener::State IntialState();
    Listener::State NextState();
    void LogRequest(SenderInetAddr request);
    void LogResponse(Packet response, SenderInetAddr request);
    void Start();

  private:
    UDPSocket *socket;
    const char *addr;
    int port;
};

#endif
