
#include <ctype.h>
#include <string.h>

#include <Logger.h>
#include <Profile/Profile.h>

#include "Add.h"

void ValidateProfileName(char* name) {

    int isValid = 1;

    for(int i = 0; name[i]; i++) {

        if(!(isalnum(name[i]) || name[i] == '-' || name[i] == '_')) {
            isValid = 0;
            break;
        }

        name[i] = tolower(name[i]);

    }

    if(!isValid) {
        Log(Error, "The name '%s' is not a valid profile name.", name);
        return;
    }

}

int AddCommand(toml_table_t* configFile, char* profileName) {

    const char* nameBuffer[32];
    int numProfiles = LoadProfileNames(configFile, nameBuffer);

    char* validatedName;
    strcpy(validatedName, profileName);
    ValidateProfileName(validatedName);

    if(strcmp(profileName, validatedName)) {
        Log(Verbose, "Name changed from '%s' to '%s'.", profileName, validatedName);
    }

    for(int i = 0; i < numProfiles; i++) {

        // Check if exists already

    }

}