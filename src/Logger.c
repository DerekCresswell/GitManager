
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Logger.h"

static int IS_VERBOSE = 0;
static int IS_COLOR = 1;

void PrintLevelTag(LogLevel lvl) {

    static const char* const ANSI_SUCCESS = "\033[0;32m";
    static const char* const ANSI_VERBOSE = "\033[0;36m";
    static const char* const ANSI_ERROR = "\033[0;31m";
    static const char* const ANSI_RESET = "\033[0m";

    switch(lvl) {
        case Success:
            printf("[%s%s", ANSI_SUCCESS, "Success");
            break;
        case Normal:
            return;
        case Verbose:
            printf("[%s%s", ANSI_VERBOSE, "Verbose");
            break;
        case Error:
            printf("[%s%s", ANSI_ERROR, "Error");
            break;
    };

    printf("%s] ", ANSI_RESET);

}

void Log(LogLevel lvl, const char* message, ...) {

    if(lvl == Verbose && !IS_VERBOSE) {
        return;
    }

    PrintLevelTag(lvl);

    va_list vaList;
    va_start(vaList, message);
    vprintf(message, vaList);
    va_end(vaList);

    printf("\n");

    if(lvl == Error) {
        exit(1);
    }

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
