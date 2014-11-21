#include "rdp_listener.h"

//RDPListener::RDPListener(UDPSocket *socket)
//{
//  current_state = IntialState();
//}

Listener::State RDPListener::IntialState()
{
  return Listener::CLOSED;
}
