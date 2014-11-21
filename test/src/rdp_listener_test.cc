#include "test_helper.h"
#include "src/rdp_listener.h"
#include "src/udp_socket.h"
#include "src/packet.h"

class MockUDPSocket : public UDPSocket {
  public:
    MockUDPSocket() : UDPSocket(0) {};
    MOCK_METHOD2(Bind,
        bool(std::string, std::string));
    MOCK_METHOD3(RecvfromNonblock,
        std::string(int maxlen, int flags, struct sockaddr *sender_inet_addr));
    MOCK_METHOD2(Send,
        int(std::string mesg, int flags));
};

using ::testing::Return;
TEST(RDPListenerTest, StateTest)
{
  MockUDPSocket sock;

  //RDPListener listener( ( (UDPSocket *) &sock ) );
  //Packet closed_to_syn_sent(SYN, 0, 0, 10240);
  //Packet syn_sent_to_established(ACK, 1, 1, 10240);
  //Packet established(DAT, 1, 1, 10240, "test");
  ////Packet established_to_fin_wait_1(FIN,
  //Packet fin_wait_2_to_time_wait(ACK

  // start listening
  //listener.start();
  // stub receive 1st part of 3 way hand shake
  // expect send 2 nd part of 3 way hand shake
  // stub receive 3 rd part of 3 way hand shake
}
