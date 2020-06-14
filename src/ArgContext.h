
#ifndef ARGCONTEXT_H
#define ARGCONTEXT_H

struct ArgContext {

    /* Options */
    int verbose;
    int color;

};
typedef struct ArgContext ArgContext;

ArgContext* ParseArguments(int argc, char* argv[]);

#endif