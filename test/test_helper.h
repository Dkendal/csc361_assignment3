#ifndef TEST_HELPER
#define TEST_HELPER value
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#define FIXTURE(FixtureClass) class FixtureClass : public ::testing::Test
#define SET_UP protected: virtual void SetUp()
#endif
