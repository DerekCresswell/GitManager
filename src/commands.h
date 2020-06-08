
#ifndef COMMANDS_H
#define COMMANDS_H

#include <toml.h>

int ListCommand(toml_table_t* configFile);

int AddCommand(toml_table_t* configFile);

int SetCommand(toml_table_t* configFile, const char* profileName, const char* path);

#endif