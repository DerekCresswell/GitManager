
#ifndef COMMANDS_SET_H
#define COMMANDS_SET_H

#include <tomlc99/toml.h>

int SetCommand(toml_table_t* configFile, const char* profileName, const char* path);

#endif