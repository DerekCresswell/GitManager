
#ifndef COMMANDS_REMOVE_H
#define COMMANDS_REMOVE_H

#include <tomlc99/toml.h>

int RemoveCommand(toml_table_t* configFile, const char* profileName, const char* pathToConfig);

#endif