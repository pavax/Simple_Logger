#ifndef SIMPLE_LOGGER_H
#define SIMPLE_LOGGER_H
#include <Arduino.h>
#include <HardwareSerial.h>

size_t const MAX_MESSAGE_LENGTH = 256;

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

void err(char const *fmt, ...);
void warn(char const *fmt, ...);
void info(char const *fmt, ...);
void debug(char const *fmt, ...);
}

#endif