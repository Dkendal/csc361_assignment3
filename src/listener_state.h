#ifndef LISTENER_STATE_H
#define LISTENER_STATE_H
namespace Listener {
  enum State {
    CLOSED,
    LISTEN,
    SYN_RECEIVED,
    ESTABLISHED,
    CLOSE_WAIT,
    LAST_ACK
  };
}
#endif
