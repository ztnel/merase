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
  #include "merase.h"
}


DEFINE_FFF_GLOBALS;
FAKE_VALUE_FUNC(pwm_code, ioctl, const char*, const char*, size_t);
FAKE_VALUE_FUNC(char*, int64_to_str, uint64_t, size_t*);
FAKE_VOID_FUNC(free_buffer, char*);

class TestMerase : public testing::Test {
  public:
    void SetUp() {
      RESET_FAKE(ioctl);
      RESET_FAKE(int64_to_str);
      RESET_FAKE(free_buffer);
      FFF_RESET_HISTORY();
    }
};

TEST_F(TestPwm, SetExportReturn) {
  pwm_code mock_ret = PWM_GENERAL_ERROR;
  ioctl_fake.return_val = mock_ret;
  int result = set_export(true);
  ASSERT_EQ(result, mock_ret);
  ASSERT_EQ(ioctl_fake.call_count, 1);
}
