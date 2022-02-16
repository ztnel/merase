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


enum Level logger_get_level();
void logger_set_level(enum Level level);
void _trace(const char *fmt, ...);
void _info(const char *fmt, ...);
void _warning(const char *fmt, ...);
void _error(const char *fmt, ...);
void _critical(const char *fmt, ...);

#ifndef critical
#define critical(...) CRITICAL(__VA_ARGS__, "")
#define CRITICAL(fmt, ...) \
  _critical("%s:%i " fmt " %s", __func__, __LINE__, __VA_ARGS__)
#endif

#ifndef error
#define error(...) ERROR(__VA_ARGS__, "")
#define ERROR(fmt, ...) \
  _error("%s:%i " fmt " %s", __func__, __LINE__, __VA_ARGS__)
#endif

#ifndef warning
#define warning(...) WARNING(__VA_ARGS__, "")
#define WARNING(fmt, ...) \
  _warning("%s:%i " fmt " %s", __func__, __LINE__, __VA_ARGS__)
#endif

#ifndef info
#define info(...) INFO(__VA_ARGS__, "")
#define INFO(fmt, ...) \
  _info("%s:%i " fmt " %s", __func__, __LINE__, __VA_ARGS__)
#endif

#ifndef trace
#define trace(...) TRACE(__VA_ARGS__, "")
#define TRACE(fmt, ...) \
  _trace("%s:%i " fmt " %s", __func__, __LINE__, __VA_ARGS__)
#endif

#endif  // MERASE_H_
