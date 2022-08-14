#ifndef SIMPLE_LOGGER_H
#define SIMPLE_LOGGER_H
#include <Arduino.h>
#include <HardwareSerial.h>

size_t const MAX_MESSAGE_LENGTH = 64;

namespace logger
{

  enum Level
  {
    None,
    Error,
    Warning,
    Info,
    Debug,
  };

  void set_serial(HardwareSerial &serial);

  void set_level(Level level);

  void err(const char *fmt, ...);
  void warn(const char *fmt, ...);
  void info(const char *fmt, ...);
  void debug(const char *fmt, ...);

  void err(const __FlashStringHelper *fmt, ...);
  void warn(const __FlashStringHelper *fmt, ...);
  void info(const __FlashStringHelper *fmt, ...);
  void debug(const __FlashStringHelper *fmt, ...);

}

#endif