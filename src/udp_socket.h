// based on ruby's udpsocket class
#ifndef SRC_UPD_SOCKET_H_
#define SRC_UPD_SOCKET_H_
#include <string>
struct SenderInetAddr;

class UDPSocket {
  public:
    UDPSocket(int ai_family) : ai_family(ai_family) {}
    virtual ~UDPSocket();

    // returns if the bind was successful
    virtual bool Bind(const char *host, int port);

    virtual void RecvFrom(int flags, SenderInetAddr *sender_addr) = 0;

    // returns number of bytes sent
    virtual int Send(const char *mesg, int flags, const char *host, int port);
  private:
    int ai_family;
};
#endif // SRC_UPD_SOCKET_H_
