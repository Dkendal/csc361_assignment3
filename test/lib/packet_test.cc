#include <gtest/gtest.h>
#include "../../lib/packet.h"

class PacketTest : public ::testing::Test
{
  protected:
  virtual void SetUp()
  {
    p = new Packet( ACK | SYN | RST, 100, 1, 10240);
  }

  Packet *p;
};

TEST_F(PacketTest, ConstructorTest)
{
  EXPECT_EQ(100, p->seqno);
  EXPECT_EQ(1, p->ackno);
  EXPECT_EQ(10240, p->window_size);
}

TEST_F(PacketTest, FlagsTest)
{
 EXPECT_TRUE(p->IsAck());
 EXPECT_TRUE(p->IsSyn());
 EXPECT_FALSE(p->IsDat());
 EXPECT_FALSE(p->IsFin());
 EXPECT_TRUE(p->IsRst());
}

TEST_F(PacketTest, ContentTest)
{
  p->SetContent("sup");
  EXPECT_EQ("sup", p->GetContent());
  EXPECT_EQ(3, p->GetContentLength());
}

TEST_F(PacketTest, ToStringTest)
{
  EXPECT_EQ("UVicCSc361 22 100 1 0 10240\n\n",  p->ToStr());
}

TEST(Packet, ParseTest)
{
  Packet p("UVicCSc361 22 100 1 0 10240\n\n");
  EXPECT_EQ("UVicCSc361", p.magic);
  EXPECT_EQ(22, p.GetFlags());
  EXPECT_EQ(100, p.seqno);
  EXPECT_EQ(1, p.ackno);
  EXPECT_EQ(10240, p.window_size);
  EXPECT_EQ(0, p.GetContentLength());
}
