/**
 * @file merase.c
 * @author Christian Sargusingh (christian@leapsystems.online)
 * @brief Basic c logger with support for precompiler directives and stdio string formatting
 * @version 0.1
 * @date 2021-12
 * 
 * @copyright Copyright © 2021 Christian Sargusingh
 * 
 */

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include "merase.h"

/**
 * @brief Set the program log level
 * 
 * @param level target logging level
 */
void logger_set_level(enum Level level) {
  _level = level;
}

/**
 * @brief Get the program log level
 * 
 * @return enum Level 
 */
enum Level logger_get_level() {
  return _level;
}

/**
 * @brief trace log endpoint
 * 
 * @param fmt format string
 * @param ... variable arguments
 */
void _trace(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  _log(TRACE, fmt, args);
  va_end(args);
}

/**
 * @brief info log endpoint
 * 
 * @param fmt format string
 * @param ... variable arguments
 */
void _info(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  _log(INFO, fmt, args);
  va_end(args);
}

/**
 * @brief warning log endpoint
 * 
 * @param fmt format string
 * @param ... variable arguments
 */
void _warning(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  _log(WARNING, fmt, args);
  va_end(args);
}


/**
 * @brief error log endpoint
 * 
 * @param fmt format string
 * @param ... variable arguments
 */
void _error(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  _log(ERROR, fmt, args);
  va_end(args);
}

/**
 * @brief critical log endpoint
 * 
 * @param fmt format string
 * @param ... variable arguments
 */
void _critical(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  _log(CRITICAL, fmt, args);
  va_end(args);
}

/**
 * @brief Filter logs by log level.
 * 
 * @param level log level
 * @param fmt format string
 * @param argp arguments passed to string formatter
 */
void _log(enum Level level, const char* fmt, va_list argp) {
  // filter output by log level
  if (_level > level) {
    return;
  }
  out(level, fmt, argp);
}

/**
 * @brief String formatting and output function. Output to stderr for ERROR and
 * CRITICAL logs.
 * 
 * @param level log level
 * @param fmt format string
 * @param argp arguments passed to string formatter
 */
void out(enum Level level, const char* fmt, va_list argp) {
  char buffer[256];
  time_t now = time(NULL);
  // set buffer with format string populated with arguments from argp
  vsnprintf(buffer, sizeof(buffer), fmt, argp);
  // print log level tag to stdout or stderr
  switch (level) {
    case TRACE:
      fprintf(stdout, "%lis [TRACE] %s\n\r", now, buffer);
      break;
    case INFO:
      fprintf(stdout, "%lis [INFO] %s\n\r", now, buffer);
      break;
    case WARNING:
      fprintf(stdout, "%lis [WARNING] %s\n\r", now, buffer);
      break;
    case ERROR:
      fprintf(stderr, "%lis [ERROR] %s\n\r", now, buffer);
      break;
    case CRITICAL:
      fprintf(stderr, "%lis [CRITICAL] %s\n\r", now, buffer);
      break;
    default:
      break;
  }
  fflush(stderr);
  fflush(stdout);
}
