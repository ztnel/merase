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

class TestMerase : public testing::Test {
  public:
    void SetUp() {
      RESET_FAKE(fprintf);
      RESET_FAKE(fflush);
      RESET_FAKE(time);
      RESET_FAKE(vfprintf);
      RESET_FAKE(pthread_mutex_lock);
      RESET_FAKE(pthread_mutex_unlock);
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

TEST_F(TestMerase, TestTraceLog) {
  merase_set_level(TRACE);
  const char *fmt = "%d";
  merase_log(TRACE, __func__, __LINE__, fmt, 1);
  ASSERT_EQ(vfprintf_fake.call_count, 1);
  ASSERT_EQ(vfprintf_fake.arg0_val, stdout);
  ASSERT_EQ(fprintf_fake.arg0_history[0], stdout);
  ASSERT_EQ(strcmp(vfprintf_fake.arg1_val, fmt), 0);
  ASSERT_EQ(pthread_mutex_lock_fake.call_count, 1);
  ASSERT_EQ(pthread_mutex_unlock_fake.call_count, 1);
  ASSERT_EQ(time_fake.call_count, 1);
}

TEST_F(TestMerase, TestInfoLog) {
  merase_set_level(INFO);
  const char *fmt = "%d";
  merase_log(INFO, __func__, __LINE__, fmt, 1);
  ASSERT_EQ(vfprintf_fake.call_count, 1);
  ASSERT_EQ(vfprintf_fake.arg0_val, stdout);
  ASSERT_EQ(fprintf_fake.arg0_history[0], stdout);
  ASSERT_EQ(strcmp(vfprintf_fake.arg1_val, fmt), 0);
  ASSERT_EQ(pthread_mutex_lock_fake.call_count, 1);
  ASSERT_EQ(pthread_mutex_unlock_fake.call_count, 1);
  ASSERT_EQ(time_fake.call_count, 1);
}

TEST_F(TestMerase, TestWarningLog) {
  merase_set_level(WARNING);
  const char *fmt = "%d";
  merase_log(WARNING, __func__, __LINE__, fmt, 1);
  ASSERT_EQ(vfprintf_fake.call_count, 1);
  ASSERT_EQ(vfprintf_fake.arg0_val, stdout);
  ASSERT_EQ(fprintf_fake.arg0_history[0], stdout);
  ASSERT_EQ(strcmp(vfprintf_fake.arg1_val, fmt), 0);
  ASSERT_EQ(pthread_mutex_lock_fake.call_count, 1);
  ASSERT_EQ(pthread_mutex_unlock_fake.call_count, 1);
  ASSERT_EQ(time_fake.call_count, 1);
}

TEST_F(TestMerase, TestErrorLog) {
  merase_set_level(ERROR);
  const char *fmt = "%d";
  merase_log(ERROR, __func__, __LINE__, fmt, 1);
  ASSERT_EQ(vfprintf_fake.call_count, 1);
  ASSERT_EQ(vfprintf_fake.arg0_val, stderr);
  ASSERT_EQ(fprintf_fake.arg0_history[0], stderr);
  ASSERT_EQ(strcmp(vfprintf_fake.arg1_val, fmt), 0);
  ASSERT_EQ(pthread_mutex_lock_fake.call_count, 1);
  ASSERT_EQ(pthread_mutex_unlock_fake.call_count, 1);
  ASSERT_EQ(time_fake.call_count, 1);
}

TEST_F(TestMerase, TestCriticalLog) {
  merase_set_level(CRITICAL);
  const char *fmt = "%d";
  merase_log(CRITICAL, __func__, __LINE__, fmt, 1);
  ASSERT_EQ(vfprintf_fake.call_count, 1);
  ASSERT_EQ(vfprintf_fake.arg0_val, stderr);
  ASSERT_EQ(fprintf_fake.arg0_history[0], stderr);
  ASSERT_EQ(strcmp(vfprintf_fake.arg1_val, fmt), 0);
  ASSERT_EQ(pthread_mutex_lock_fake.call_count, 1);
  ASSERT_EQ(pthread_mutex_unlock_fake.call_count, 1);
  ASSERT_EQ(time_fake.call_count, 1);
}