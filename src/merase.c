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

struct __std_log {
  FILE* fp;
  int line;
  va_list argp;
  const char* fmt;
  const char *repr;
  const char *func;
};

// program log level (disable by default)
static enum Level _level = DISABLE;
static pthread_mutex_t s_mutx;
static char *_get_level_str(enum Level level);
static void _out(struct __std_log *stdl);

/**
 * @brief Set the program log level
 * 
 * @param level target logging level
 */
void merase_set_level(enum Level level) {
  _level = level;
}

/**
 * @brief Get the program log level
 * 
 * @return enum Level 
 */
enum Level merase_get_level() {
  return _level;
}

/**
 * @brief Filter logs by log level.
 * 
 * @param level log level
 * @param fmt format string
 * @param argp arguments passed to string formatter
 */
void merase_log(enum Level level, const char* func, int line, const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  // filter output by log level
  if (_level > level) {
    return;
  }
  struct __std_log stdl;
  if (level >= ERROR) {
    stdl.fp = stderr;
  } else {
    stdl.fp = stdout;
  }
  stdl.repr = _get_level_str(level);
  stdl.argp = args;
  stdl.fmt = fmt;
  stdl.func = func;
  stdl.line = line;
  _out(&stdl);
  va_end(args);
}

/**
 * @brief Get the string representation of log level enum
 * 
 * @param level log level
 * @return char* 
 */
static char *_get_level_str(enum Level level) {
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
static void _out(struct __std_log *stdl) {
  time_t now = time(NULL);
  FILE *fp = stdl->fp;
  pthread_mutex_lock(&s_mutx);
  fprintf(fp, "%ld [%s]\t %s:%i ",
    now, stdl->repr, stdl->func, stdl->line);
  vfprintf(fp, stdl->fmt, stdl->argp);
  fprintf(fp, "\n\r");
  fflush(fp);
  pthread_mutex_unlock(&s_mutx);
}
