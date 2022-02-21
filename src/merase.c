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

/**
 * @brief Standard logging struct
 * 
 */
struct __std_log {
  FILE *fp;
  int line;
  va_list *argp;
  const char *fmt;
  const char *repr;
  const char *func;
};

// program log level (disable by default)
static enum Level _level = DISABLE;
// mutex for file consumption
static pthread_mutex_t f_mutx;
// mutex for accessing level
static pthread_mutex_t l_mutx;
static char *_get_level_str(enum Level level);
static void _out(struct __std_log *stdl);

/**
 * @brief Set the program log level
 * 
 * @param level target logging level
 */
void merase_set_level(enum Level level) {
  pthread_mutex_lock(&l_mutx);
  _level = level;
  pthread_mutex_unlock(&l_mutx);
}

/**
 * @brief Get the program log level
 * 
 * @return enum Level 
 */
enum Level merase_get_level() {
  pthread_mutex_lock(&l_mutx);
  enum Level lvl = _level;
  pthread_mutex_unlock(&l_mutx);
  return lvl;
}

/**
 * @brief Perform log filtration and standard log construction parsing variable arguments
 * 
 * @param level log level enum
 * @param func macro expanded log containing function name
 * @param line macro expanded log line
 * @param fmt log string formatter
 * @param ... variable arguments for string formatter
 */
void merase_log(enum Level level, const char* func, int line, const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  // filter output by log level
  if (merase_get_level() > level) {
    return;
  }
  struct __std_log stdl;
  if (level >= ERROR) {
    stdl.fp = stderr;
  } else {
    stdl.fp = stdout;
  }
  stdl.repr = _get_level_str(level);
  stdl.argp = &args;
  stdl.fmt = fmt;
  stdl.func = func;
  stdl.line = line;
  _out(&stdl);
  va_end(args);
}

/**
 * @brief Get the string representation of log level enum
 * 
 * @param level log level enum
 * @return char* 
 */
static char *_get_level_str(enum Level level) {
  switch (level) {
    case TRACE: return "TRACE";
    case INFO: return "INFO";
    case WARNING: return "WARN";
    case ERROR: return "ERROR";
    default: return "CRIT";
  }
}

/**
 * @brief Static IO output function for log message
 * 
 * @param stdl standard log out struct containing log metrics
 */
static void _out(struct __std_log *stdl) {
  time_t now = time(NULL);
  FILE *fp = stdl->fp;
  pthread_mutex_lock(&f_mutx);
  fprintf(fp, "%ld [%s]\t %s:%i ", now, stdl->repr, stdl->func, stdl->line);
  vfprintf(fp, stdl->fmt, *stdl->argp);
  fprintf(fp, "\n\r");
  fflush(fp);
  pthread_mutex_unlock(&f_mutx);
}
