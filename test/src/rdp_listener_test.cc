#include "test_helper.h"
#include "src/rdp_listener.h"
#include "src/udp_socket.h"
#include "src/packet.h"


using ::testing::Return;
TEST(RDPListenerTest, StateTest)
{
  //MockUDPSocket sock;

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
