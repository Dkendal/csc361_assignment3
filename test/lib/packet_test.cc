#include <gtest/gtest.h>
#include "../../lib/packet.h"

class PacketTest : public ::testing::Test
{
  protected:
  virtual void SetUp()
  {
    p = new Packet( ACK | SYN, 100, 1 );
  }

  Packet *p;
};

class ContentTest : public ::testing::Test
{
  protected:
  virtual void SetUp()
  {
    p = new Packet(0, 0, 0);
    p->SetContent("sup");
  }

  Packet *p;
};

TEST_F(PacketTest, FlagsTest)
{
 EXPECT_TRUE(p->IsAck());
 EXPECT_TRUE(p->IsSyn());
 EXPECT_FALSE(p->IsDat());
 EXPECT_FALSE(p->IsFin());
 EXPECT_FALSE(p->IsRst());
}

//TEST_F(PacketTest, Constructor)
//{
//  EXPECT_EQ(100, p->seqno);
//  EXPECT_EQ(1, p->ackno);
//}
//
TEST_F(PacketTest, TestName)
{

}


TEST_F(ContentTest, SetsContent)
{
  EXPECT_EQ("sup", p->GetContent());
}

// TEST_F(ContentTest, SetsChecksum)
// {
//   std::cout << __cplusplus << std::endl;
//   EXPECT_EQ("", p->GetChecksum());
// }
