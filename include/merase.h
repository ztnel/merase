/**
 * @file merase.h
 * @author Christian Sargusingh (christian@leapsystems.online)
 * @brief Basic c logger with support for precompiler directives and stdio string formatting
 * @version 0.1
 * @date 2022-12
 * 
 * @copyright Copyright © 2021 Christian Sargusingh
 * 
 */
#ifndef MERASE_H_
#define MERASE_H_
#include <stdio.h>

// logging levels
enum Level {
  TRACE,
  INFO,
  WARNING,
  ERROR,
  CRITICAL,
  DISABLE
};


enum Level merase_get_level();
void merase_set_level(enum Level level);
void merase_log(enum Level level, const char* func, int line, const char* fmt, ...);

#ifndef critical
#define critical(...) __CRITICAL(__VA_ARGS__, "")
#define __CRITICAL(fmt, ...) \
  merase_log(CRITICAL, __func__, __LINE__, fmt, __VA_ARGS__)
#endif

#ifndef error
#define error(...) __ERROR(__VA_ARGS__, "")
#define __ERROR(fmt, ...) \
  merase_log(ERROR, __func__, __LINE__, fmt, __VA_ARGS__)
#endif

#ifndef warning
#define warning(...) __WARNING(__VA_ARGS__, "")
#define __WARNING(fmt, ...) \
  merase_log(WARNING, __func__, __LINE__, fmt, __VA_ARGS__)
#endif

#ifndef info
#define info(...) __INFO(__VA_ARGS__, "")
#define __INFO(fmt, ...) \
  merase_log(INFO, __func__, __LINE__, fmt, __VA_ARGS__)
#endif

#ifndef trace
#define trace(...) __TRACE(__VA_ARGS__, "")
#define __TRACE(fmt, ...) \
  merase_log(TRACE, __func__, __LINE__, fmt, __VA_ARGS__)
#endif

#endif  // MERASE_H_
