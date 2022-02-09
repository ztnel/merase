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
      logger_set_level(TRACE);
    }
    void TearDown() {}
};

TEST_F(TestMerase, TestGetSetLogLevel) {
  logger_set_level(INFO);
  ASSERT_EQ(logger_get_level(), INFO);
}

TEST_F(TestMerase, TestLogFiltering) {
  logger_set_level(WARNING);
  _info("filtration test %d", 1);
  ASSERT_EQ(fprintf_fake.call_count, 0);
}

TEST_F(TestMerase, TestTraceLog) {
  const char* msg = "trace log test %d";
  _trace(msg, 1);
  ASSERT_EQ(fprintf_fake.call_count, 1);
  ASSERT_EQ(fprintf_fake.arg0_val, stdout);
}

TEST_F(TestMerase, TestInfoLog) {
  const char* msg = "info log test %d";
  _info(msg, 1);
  ASSERT_EQ(fprintf_fake.call_count, 1);
  ASSERT_EQ(fprintf_fake.arg0_val, stdout);
}

TEST_F(TestMerase, TestWarningLog) {
  const char* msg = "warning log test %d";
  _warning(msg, 1);
  ASSERT_EQ(fprintf_fake.call_count, 1);
  ASSERT_EQ(fprintf_fake.arg0_val, stdout);
}

TEST_F(TestMerase, TestErrorLog) {
  const char* msg = "error log test %d";
  _error(msg, 1);
  ASSERT_EQ(fprintf_fake.call_count, 1);
  ASSERT_EQ(fprintf_fake.arg0_val, stderr);
}

TEST_F(TestMerase, TestCriticalLog) {
  const char* msg = "critical log test %d";
  _critical(msg, 1);
  ASSERT_EQ(fprintf_fake.call_count, 1);
  ASSERT_EQ(fprintf_fake.arg0_val, stderr);
}
