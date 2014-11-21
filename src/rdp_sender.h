#ifndef RDP_SENDER_H
#define RDP_SENDER_H value

enum SenderState {
  CLOSED,
  SYN_SENT,
  ESTABLISHED,
  CLOSE_WAIT,
  LAST_ACK
};

class RDPSender
{
public:
  RDPSender();
  ~RDPSender();

private:
  SenderState state;
  /* data */
};
#endif
