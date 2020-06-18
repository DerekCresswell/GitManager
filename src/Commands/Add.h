
#ifndef COMMANDS_ADD_H
#define COMMANDS_ADD_H

#include <tomlc99/toml.h>

int AddCommand(toml_table_t* configFile, char* profileName);

#endif