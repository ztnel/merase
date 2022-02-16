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
#include <pthread.h>
#include "merase.h"

struct __std_level {
  FILE* fp;
  const char *repr;
};

// program log level (disable by default)
static enum Level _level = DISABLE;
static pthread_mutex_t s_mutx;
static char *get_level_str(enum Level level);
static void _log(enum Level level, const char* fmt, va_list argp);
static void out(struct __std_level *stdl, const char* fmt, va_list argp);

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
 * @param ... variable arguments for string fmt
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
static void _log(enum Level level, const char* fmt, va_list argp) {
  // filter output by log level
  if (_level > level) {
    return;
  }
  struct __std_level stdl;
  if (level >= ERROR) {
    stdl.fp = stderr;
  } else {
    stdl.fp = stdout;
  }
  stdl.repr = get_level_str(level);
  out(&stdl, fmt, argp);
}

/**
 * @brief Get the string representation of log level enum
 * 
 * @param level log level
 * @return char* 
 */
static char *get_level_str(enum Level level) {
  switch (level) {
    case TRACE: return "TRACE";
    case INFO: return "INFO";
    case WARNING: return "WARN";
    case ERROR: return "ERROR";
    case CRITICAL: return "CRIT";
    default: return "NULL";
  }
}

/**
 * @brief Pre log message formatting and file write function
 * 
 * @param level log level
 * @param fmt format string
 * @param argp arguments passed to string formatter
 */
static void out(struct __std_level *stdl, const char *fmt, va_list argp) {
  time_t now = time(NULL);
  pthread_mutex_lock(&s_mutx);
  fprintf(stdl->fp, "%ld [%s]\t", now, stdl->repr);
  vfprintf(stdl->fp, fmt, argp);
  fprintf(stdl->fp, "\n\r");
  fflush(stdl->fp);
  pthread_mutex_unlock(&s_mutx);
}
