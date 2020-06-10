
#include <stdlib.h>
#include <string.h>

#include "Set.h"

int SetCommand(toml_table_t* configFile, const char* profileName, const char* path) {

    toml_table_t* profileTable = toml_table_in(configFile, profileName);
    if(profileTable == 0) {
        printf("%s is not a profile.", profileName);
        return 1;
    }

    char buff[1024] = "git config --local user.name ";
    system(strcat(buff, toml_raw_in(profileTable, "userName")));
    memset(buff, 0, 1024);
    strcpy(buff, "git config --local user.email ");
    system(strcat(buff, toml_raw_in(profileTable, "userEmail")));

}