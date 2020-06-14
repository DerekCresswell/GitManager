
#include <stdlib.h>
#include <unistd.h>

#include <Logger.h>

#include "ArgContext.h"

ArgContext* ParseArguments(int argc, char* argv[]) {

    if(argc < 2) {
        Log(Error, "gitmanager requires a command to be passed in.");
        return NULL;
    }

    ArgContext* argContext = malloc(sizeof *argContext);

    int arg;
    while((arg = getopt(argc, argv, "vc")) != -1) {

        switch (arg) {

            case 'v':
                argContext->verbose = 1;
                break;

            case 'c':
                argContext->color = 1;
                break;

            default:
                break;

        }

    }

    return argContext;

}