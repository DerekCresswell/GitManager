
#include <stdlib.h>
#include <unistd.h>

#include <Logger.h>

#include "ArgContext.h"

ArgContext* ParseArguments(int argc, char* argv[]) {

    if(argc < 2) {
        Log(Error, "gitmanager requires a command to be passed in.\nTry running 'gitmanager help'.");
        return NULL;
    }

    ArgContext* argContext = malloc(sizeof *argContext);

    /* Set defaults */
    argContext->verbose = 0;
    argContext->color = 1;

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