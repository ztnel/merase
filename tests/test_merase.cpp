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

extern "C" {
  #include <fff.h>
  #include <stdio.h>
  #include <pthread.h>
  #include "merase.h"
}


DEFINE_FFF_GLOBALS;
FAKE_VALUE_FUNC_VARARG(int, fprintf, FILE *, const char *, ...);
FAKE_VALUE_FUNC3(int, vfprintf, FILE *, const char *, char *);
FAKE_VALUE_FUNC1(int, fflush, FILE *);
FAKE_VALUE_FUNC1(int, pthread_mutex_lock, pthread_mutex_t *)
FAKE_VALUE_FUNC1(int, pthread_mutex_unlock, pthread_mutex_t *)

class TestMerase : public testing::Test {
  public:
    void SetUp() {
      RESET_FAKE(fprintf);
      RESET_FAKE(fflush);
      FFF_RESET_HISTORY();
      merase_set_level(DISABLE);
    }
};

TEST_F(TestMerase, TestGetSetLogLevel) {
  for (int i=TRACE; i <= DISABLE; i++) {
    merase_set_level((Level)i);
    ASSERT_EQ(merase_get_level(), (Level)i);
  }
}

TEST_F(TestMerase, TestLogFiltering) {
  const char* fmt = "filtration test";
  // test up to but not including TRACE (no filtering)
  for (int i=DISABLE; i > TRACE; i--) {
    merase_set_level((Level)i);
    merase_log((Level)(i - 1), __func__, __LINE__, "%d", 1);
    ASSERT_EQ(vfprintf_fake.call_count, 0);
  }
}

// TEST_F(TestMerase, TestTraceLog) {
//   merase_set_level(TRACE);
//   const char* msg = "trace log test %d";
//   _trace(msg, 1);
//   ASSERT_EQ(fprintf_fake.call_count, 1);
//   ASSERT_EQ(fprintf_fake.arg0_val, stdout);
// }

// TEST_F(TestMerase, TestInfoLog) {
//   logger_set_level(INFO);
//   const char* msg = "info log test %d";
//   _info(msg, 1);
//   ASSERT_EQ(fprintf_fake.call_count, 1);
//   ASSERT_EQ(fprintf_fake.arg0_val, stdout);
// }

// TEST_F(TestMerase, TestWarningLog) {
//   logger_set_level(WARNING);
//   const char* msg = "warning log test %d";
//   _warning(msg, 1);
//   ASSERT_EQ(fprintf_fake.call_count, 1);
//   ASSERT_EQ(fprintf_fake.arg0_val, stdout);
// }

// TEST_F(TestMerase, TestErrorLog) {
//   logger_set_level(ERROR);
//   const char* msg = "error log test %d";
//   _error(msg, 1);
//   ASSERT_EQ(fprintf_fake.call_count, 1);
//   ASSERT_EQ(fprintf_fake.arg0_val, stderr);
// }

// TEST_F(TestMerase, TestCriticalLog) {
//   logger_set_level(CRITICAL);
//   const char* msg = "critical log test %d";
//   _critical(msg, 1);
//   ASSERT_EQ(fprintf_fake.call_count, 1);
//   ASSERT_EQ(fprintf_fake.arg0_val, stderr);
// }
