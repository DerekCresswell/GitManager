
#include <stdio.h>

#include "Help.h"

void HelpCommand(void) {

    // This does not use the logger to avoid new lines.
    printf(\
        "Gitmanager. A CLI tool to manage git configuration.\n"
        "Usage: gitmanager <command> [-vc]\n\n"
        "Possible commands are :\n"
        "  list          : Lists all currently available profiles.\n"
        "  add <name>    : Adds a profile named 'name' to your list.\n"
        "  remove <name> : Removes a profile named 'name' from the available profiles.\n"
        "  set <name>    : Sets the configuration of 'name' on the current working directory.\n"
        "  help          : Shows this out put.\n\n"
        "Possible arguments :\n"
        "  -v : Prints verbose messages.\n"
        "  -c : Prints ANSI colored tags on messages.\n"
    );

}