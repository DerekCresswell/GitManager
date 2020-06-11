
#include <stdarg.h>
#include <stdio.h>

#include "Logger.h"

static int IS_VERBOSE = 0;
static int IS_COLOR = 1;

const char* GetANSIColor(LogLevel lvl) {

    static const char* const ANSI_SUCCESS = "\033[0;32m";
    static const char* const ANSI_VERBOSE = "\033[0;36m";
    static const char* const ANSI_ERROR = "\033[0;31m";

    if(!IS_COLOR) {
        return "";
    }

    switch(lvl) {
        case Success:
            return ANSI_SUCCESS;
        case Normal:
            return "";
        case Verbose:
            return ANSI_VERBOSE;
        case Error:
            return ANSI_ERROR;
    };

}

const char* GetANSIEnd(LogLevel lvl) {

    static const char* const ANSI_RESET = "\033[0m";

    if(!IS_COLOR || lvl == Normal) {
        return "";
    }

    return ANSI_RESET;

}

void Log(LogLevel lvl, const char* message, ...) {

    if(lvl == Verbose && !IS_VERBOSE) {
        return;
    }

    printf("%s", GetANSIColor(lvl));

    va_list vaList;
    va_start(vaList, message);
    printf(message, vaList);
    va_end(vaList);

    printf("%s\n", GetANSIEnd(lvl));

}

void InitLog(ArgContext* argContext) {

    static int initialized = 0;
    if(initialized) {
        return;
    }
    initialized = 1;

    IS_VERBOSE = argContext->verbose;
    IS_COLOR = argContext->color;

}
