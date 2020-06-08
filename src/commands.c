
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "commands.h"
#include "profile.h"

int ListCommand(toml_table_t* configFile) {

    // Want a better way to declare this size.
    const char* nameBuffer[32];
    int numProfiles = LoadProfileNames(configFile, nameBuffer);

    if(numProfiles == 0) {
        printf("There are no available profiles.\n");
        return 0;
    }

    printf("Here are the available profiles :\n");

    for(int i = 0; i < numProfiles; i++) {

        // Temp, strip quotation marks
        char nameTemp[strlen(nameBuffer[i])];
        strcpy(nameTemp, nameBuffer[i]);
        char* namePtr = nameTemp;
        namePtr++;
        namePtr[strlen(namePtr) - 1] = 0;

        printf("  %d : %s", i + 1, namePtr);

        // Description
        toml_table_t* profileTable = toml_table_in(configFile, namePtr);
        if(profileTable == 0) {
            printf("\n");
            continue;
        }

        const char* description = toml_raw_in(profileTable, "description");
        if(description == 0) {
            printf("\n");
            continue;
        }

        printf(", %s\n", description);

    }

}

int AddCommand(toml_table_t* configFile) {

}

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