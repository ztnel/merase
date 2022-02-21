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
  #include <stdarg.h>
  #include "merase.h"
}


DEFINE_FFF_GLOBALS;
FAKE_VALUE_FUNC_VARARG(int, fprintf, FILE *, const char *, ...);
FAKE_VALUE_FUNC1(time_t, time, time_t *);
FAKE_VALUE_FUNC3(int, vfprintf, FILE *, const char *, va_list);
FAKE_VALUE_FUNC1(int, fflush, FILE *);
FAKE_VALUE_FUNC1(int, pthread_mutex_lock, pthread_mutex_t *)
FAKE_VALUE_FUNC1(int, pthread_mutex_unlock, pthread_mutex_t *)

#define FFF_FAKES_LIST(FAKE)  \
  FAKE(fprintf)               \
  FAKE(time)                  \
  FAKE(vfprintf)              \
  FAKE(fflush)                \
  FAKE(pthread_mutex_lock)    \
  FAKE(pthread_mutex_unlock)

class TestMerase : public testing::Test {
  public:
    void SetUp() {
      FFF_FAKES_LIST(RESET_FAKE);
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

TEST_F(TestMerase, TestLogging) {
  const char *fmt = "%d";
  for (int i = CRITICAL; i >= TRACE; i--) {
    Level level = (Level)i;
    FILE *fp = level < 3 ? stdout : stderr;
    merase_set_level(level);
    merase_log(level, __func__, __LINE__, fmt, 1);
    ASSERT_EQ(vfprintf_fake.call_count, 1);
    ASSERT_EQ(vfprintf_fake.arg0_val, fp);
    ASSERT_EQ(fprintf_fake.arg0_history[0], fp);
    ASSERT_EQ(strcmp(vfprintf_fake.arg1_val, fmt), 0);
    ASSERT_EQ(time_fake.call_count, 1);
    ASSERT_EQ(fflush_fake.call_count, 1);
    ASSERT_EQ(fflush_fake.arg0_val, fp);
    RESET_FAKE(fprintf);
    RESET_FAKE(fflush);
    RESET_FAKE(time);
    RESET_FAKE(vfprintf);
  }
}
