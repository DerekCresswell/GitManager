
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

int AddCommand(toml_table_t* configFile, char* profileName, const char* pathToConfig) {

    const char* nameBuffer[32];
    int numProfiles = LoadProfileNames(configFile, nameBuffer);

    char validatedName[strlen(profileName)];
    strcpy(validatedName, profileName);
    ValidateProfileName(validatedName);

    if(strcmp(profileName, validatedName)) {
        Log(Verbose, "Name changed from '%s' to '%s'.", profileName, validatedName);
    }

    for(int i = 0; i < numProfiles; i++) {

        if(strcmp(validatedName, nameBuffer[i]) == 0) {
            Log(Error, "The name '%s' already exists.", validatedName);
            return 0;
        }

    }

    FILE* currentFile = fopen(pathToConfig, "r");
    if(!currentFile) {
        Log(Error, "Could not open file '%s'.", pathToConfig);
        return 0;
    }

    const char* tempSuffix = ".temp";
    char newPathToConfig[strlen(pathToConfig) + strlen(tempSuffix)];
    newPathToConfig[0] = '\0';
    strcat(newPathToConfig, pathToConfig);
    strcat(newPathToConfig, tempSuffix);

    FILE* newFile = fopen(newPathToConfig, "w");
    if(!newFile) {
        Log(Error, "Could not create file '%s'.", newPathToConfig);
        return 0;
    }
    Log(Verbose, "Opened temporary file at '%s'.", newPathToConfig);

    char curLine[256];
    while(fgets(curLine, sizeof(curLine), currentFile)) {

        fputs(curLine, newFile);

    }

    fclose(currentFile);
    fclose(newFile);
    remove(newPathToConfig);

}