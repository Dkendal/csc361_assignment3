#include "src/rdp_listener.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <sstream>

#include "src/packet.h"
#include "src/sender_inet_addr.h"
#include "src/udp_socket.h"
#include "test/test_helper.h"

using ::testing::Return;
using ::testing::_;
using ::testing::InSequence;
using ::testing::SetArgPointee;
using ::testing::DoAll;
using ::testing::StrEq;


class MockUDPSocket : public UDPSocket {
  public:
    MockUDPSocket() : UDPSocket(0) {}
    MOCK_METHOD2(Bind,
        bool(const char *addr, int port));
    MOCK_METHOD2(RecvFrom,
        void(int flags, SenderInetAddr *sender_addr));
    MOCK_METHOD4(Send,
        int(const char *mesg, int flags, const char *host, int port));
};

void StubRequest(MockUDPSocket *sock,
    const char *request,
    const char *addr,
    int port) {
  SenderInetAddr result = {};
  result.content = request;
  result.addr = addr;
  result.port = port;
  result.ai_family = AF_INET;

  EXPECT_CALL(*sock, RecvFrom(_, _)).WillOnce(SetArgPointee<1>(result));
}

TEST(RDPListenerTest, SuccessfulTransferTest) {
  MockUDPSocket sock;

  const char *target_addr = "123.123.123.123";
  int port = 3000;

  {
    InSequence s;

    EXPECT_CALL(sock, Bind(StrEq("100.100.100.100"), 9000)).WillOnce(Return(true));

    StubRequest(&sock, "UVicCSc361 4 0 0 0 10240\n\n", target_addr, port);
    EXPECT_CALL(sock, Send(StrEq("UVicCSc361 2 0 1 0 10240\n\n"), _, StrEq(target_addr), port));

    StubRequest(&sock, "UVicCSc361 1 1 1 4 10240\n\ntest", target_addr, port);
    EXPECT_CALL(sock, Send(StrEq("UVicCSc361 2 0 5 0 10240\n\n"), _, StrEq(target_addr), port));

    StubRequest(&sock, "UVicCSc361 1 5 1 4 10240\n\n1234", target_addr, port);
    EXPECT_CALL(sock, Send(StrEq("UVicCSc361 2 0 9 0 10240\n\n"), _, StrEq(target_addr), port));

    StubRequest(&sock, "UVicCSc361 8 9 1 0 10240\n\n", target_addr, port);
    EXPECT_CALL(sock, Send(StrEq("UVicCSc361 2 0 10 0 10240\n\n"), _, target_addr, port));
  }

  RDPListener listener(&sock, "100.100.100.100", 9000);
  listener.Start();
}

TEST(RDPListenerTest, DroppedPacketTest) {
  MockUDPSocket sock;

  const char *target_addr = "123.123.123.123";
  int port = 3000;

  {
    InSequence s;

    EXPECT_CALL(sock, Bind(StrEq("100.100.100.100"), 9000)).WillOnce(Return(true));

    //syn
    StubRequest(&sock, "UVicCSc361 4 0 0 0 10240\n\n", target_addr, port);
    //ack
    EXPECT_CALL(sock, Send(StrEq("UVicCSc361 2 0 1 0 10240\n\n"), _, StrEq(target_addr), port));

    //dat
    StubRequest(&sock, "UVicCSc361 1 5 1 4 10240\n\n1234", target_addr, port);
    //ack
    EXPECT_CALL(sock, Send(StrEq("UVicCSc361 2 0 1 0 10240\n\n"), _, StrEq(target_addr), port));

    //dat
    StubRequest(&sock, "UVicCSc361 1 1 1 4 10240\n\ntest", target_addr, port);
    //ack
    EXPECT_CALL(sock, Send(StrEq("UVicCSc361 2 0 5 0 10240\n\n"), _, StrEq(target_addr), port));

    //dat
    StubRequest(&sock, "UVicCSc361 1 5 1 4 10240\n\n1234", target_addr, port);
    //ack
    EXPECT_CALL(sock, Send(StrEq("UVicCSc361 2 0 9 0 10240\n\n"), _, StrEq(target_addr), port));

    //fin
    StubRequest(&sock, "UVicCSc361 8 9 1 0 10240\n\n", target_addr, port);
    //ack
    EXPECT_CALL(sock, Send(StrEq("UVicCSc361 2 0 10 0 10240\n\n"), _, target_addr, port));
  }

  RDPListener listener(&sock, "100.100.100.100", 9000);
  listener.Start();
}
