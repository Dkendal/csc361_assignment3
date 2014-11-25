#ifndef SRC_SENDER_INET_ADDR_H_
#define SRC_SENDER_INET_ADDR_H_

struct SenderInetAddr {
  const char *content, *addr;
  int ai_family, port;
};

#endif // SRC_SENDER_INET_ADDR_H_
