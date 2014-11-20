#include <gtest/gtest.h>
#include "../../lib/rdp.h"

TEST(RDPTest, ValidConstructor)
{
  RDP rdp("localhost", "9000");
}
