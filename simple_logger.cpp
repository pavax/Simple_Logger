#include <cstdarg>
//#include <cstdint>
#include <cstdio>
#include <cstring>
#include "simple_logger.h"
#include <HardwareSerial.h>

namespace logger
{

  Level log_level = None;

  HardwareSerial serialOut = NULL;

  char logBuf[MAX_MESSAGE_LENGTH];

  void set_serial(HardwareSerial &serial)
  {
    serialOut = serial;
  }

  void set_level(Level level)
  {
    log_level = level;
  }

  void serialPrintf(const char *level_name, const char *message)
  {
    if (serialOut != NULL)
      serialOut.printf("%s: %s\n", level_name, message);
  }

  static void log(const char *level_name, const char *fmt, va_list as)
  {
    vsnprintf(logBuf, MAX_MESSAGE_LENGTH, fmt, as);
    serialPrintf(level_name, logBuf);
  }

#define DEFINE_LOGGING_FUNCTION(name, level) \
  void name(const char *fmt, ...)            \
  {                                          \
    if (log_level < level)                   \
      return;                                \
                                             \
    va_list as;                              \
    va_start(as, fmt);                       \
    log(#name, fmt, as);                     \
    va_end(as);                              \
  }

#define DEFINE_LOGGING_FUNCTION2(name, level)       \
  void name(const __FlashStringHelper *fmt, ...) \
  {                                                 \
    if (log_level < level)                          \
      return;                                       \
                                                    \
    va_list as;                                     \
    va_start(as, fmt);                           \
    log(#name, (PGM_P)(fmt), as);                \
    va_end(as);                                     \
  }

  DEFINE_LOGGING_FUNCTION(err, Error);
  DEFINE_LOGGING_FUNCTION(warn, Warning);
  DEFINE_LOGGING_FUNCTION(info, Info);
  DEFINE_LOGGING_FUNCTION(debug, Debug);

  DEFINE_LOGGING_FUNCTION2(err, Error);
  DEFINE_LOGGING_FUNCTION2(warn, Warning);
  DEFINE_LOGGING_FUNCTION2(info, Info);
  DEFINE_LOGGING_FUNCTION2(debug, Debug);
}
