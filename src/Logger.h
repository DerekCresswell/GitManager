
#ifndef LOGGER_H
#define LOGGER_H

#include <ArgContext.h>

// Defines the logging levels.
// If 'Error' is specified the program will exit.
enum LogLevel {
    Success,
    Normal,
    Verbose,
    Error
};
typedef enum LogLevel LogLevel;

// Logs a message based on error level.
void Log(LogLevel lvl, const char* message, ...);

// Call once at the start to setup configuration.
void InitLog(ArgContext* argContext);

#endif