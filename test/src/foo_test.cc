#include "test/test_helper.h"
#include "src/foo.h"


class MockFoo : public Foo {
 public:
  MOCK_METHOD0(Bar,
      int());
};

using ::testing::Return;
TEST(MethodUnderTest, TestName)
{
  MockFoo foo;
  EXPECT_CALL(foo, Bar()).WillOnce(Return(5));
  EXPECT_EQ(5, foo.Bar());
}
