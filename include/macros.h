#ifndef MACROS_H
#define MACROS_H

#ifdef TESTING
#include <stdio.h>
#define LOG_ERROR(fmt, ...) \
  fprintf(stderr, "%s:%d (%s):\t" fmt "\n", \
      __FILE__, __LINE__, __func__, ##__VA_ARGS__)

#define LOG_INFO(fmt, ...) \
  fprintf(stdout, "%s:%d (%s):\t" fmt "\n", \
      __FILE__, __LINE__, __func__, ##__VA_ARGS__)

#define LOG_WARN(fmt, ...) \
  fprintf(stdout, "%s:%d (%s):\t" fmt "\n", \
      __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#else
#define LOG_ERROR(...) ((void) 0)
#define LOG_INFO(...) ((void) 0)
#define LOG_WARN(...) ((void) 0)
#endif // TESTING

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#endif // MACROS_H
