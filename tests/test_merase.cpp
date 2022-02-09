/**
 * @file test_merase.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-02
 * 
 * @copyright Copyright © 2022 Christian Sargusingh
 * 
 */

#include <gtest/gtest.h>
#include <fff.h>

extern "C" {
  #include <stdio.h>
  #include "merase.h"
}


DEFINE_FFF_GLOBALS;
FAKE_VALUE_FUNC_VARARG(int, fprintf, FILE *, const char *, ...);

class TestMerase : public testing::Test {
  public:
    void SetUp() {
      RESET_FAKE(fprintf);
      FFF_RESET_HISTORY();
    }
};

TEST_F(TestMerase, TestTraceLog) {
  _trace("Hello this is a test");
  ASSERT_EQ(fprintf_fake.call_count, 1);
}
