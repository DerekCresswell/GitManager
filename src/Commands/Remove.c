
#include <ctype.h>
#include <string.h>

#include <Logger.h>
#include <Profile/Profile.h>

#include "Remove.h"

int RemoveCommand(toml_table_t* configFile, const char* profileName, const char* pathToConfig) {

    const char* nameBuffer[MAX_PROFILE_NAME_SIZE];
    int numProfiles = LoadProfileNames(configFile, nameBuffer);

    int profileNameExists = 0;
    for(int i = 0; i < numProfiles; i++) {

        if(strcmp(profileName, nameBuffer[i]) == 0) {
            profileNameExists = 1;
            break;
        }

    }

    if(!profileNameExists) {
        Log(Error, "The name '%s' does not exist exist.", profileName);
        return 1;
    }

    FILE* currentFile = fopen(pathToConfig, "r");
    if(!currentFile) {
        Log(Error, "Could not open file '%s'.", pathToConfig);
        return 0;
    }

    const char* tempSuffix = ".temp";
    char newPathToConfig[strlen(pathToConfig) + strlen(tempSuffix)];
    strcpy(newPathToConfig, pathToConfig);
    strcat(newPathToConfig, tempSuffix);

    FILE* newFile = fopen(newPathToConfig, "w");
    if(!newFile) {
        Log(Error, "Could not create file '%s'.", newPathToConfig);
        return 0;
    }
    Log(Verbose, "Opened temporary file at '%s'.", newPathToConfig);

    char curLine[256];

    int profileNameFound = 0;
    int profileDefinitionFound = 0;
    int profileDefinitionErased = 0;

    while(fgets(curLine, sizeof(curLine), currentFile)) {

        char modLine[strlen(curLine) + 1];

        // Trim leading and trailing whitespace.
        int j = 0;
        int front = 0;
        for(int i = 0; curLine[i] != '\n' && curLine[i] != '\0'; i++) {

            if(isspace(curLine[i]) && !front) {
                continue;
            }

            front = 1;
            modLine[j] = curLine[i];
            j++;

        }
        modLine[j++] = '\n';
        modLine[j] = '\0';

        if(!profileNameFound) {

            // Max name size, plus quotes, comma, and new line.
            char profileNameWatch[MAX_PROFILE_NAME_SIZE + 4] = "\"";
            strcat(profileNameWatch, profileName);
            strcat(profileNameWatch, "\",\n");

            if(strcmp(modLine, profileNameWatch) == 0) {
                profileNameFound = 1;
                continue;
            }

        }

        if(!profileDefinitionFound) {

            char profileDefinitionWatch[MAX_PROFILE_NAME_SIZE + 3] = "[";
            strcat(profileDefinitionWatch, profileName);
            strcat(profileDefinitionWatch, "]\n");

            if(strcmp(modLine, profileDefinitionWatch) == 0) {
                profileDefinitionFound = 1;
                continue;
            }

        }

        if(!profileDefinitionErased && profileDefinitionFound) {

            if(strcmp(modLine, "\n") == 0) {
                profileDefinitionErased = 1;
            }

            continue;

        }

        fputs(curLine, newFile);

    }

    fclose(currentFile);
    fclose(newFile);
    Log(Verbose, "Temporary file '%s' written successfully.", newPathToConfig);
    Log(Verbose, "Copying '%s' to '%s'.", newPathToConfig, pathToConfig);

    currentFile = fopen(pathToConfig, "w");
    newFile = fopen(newPathToConfig, "r");
    while(fgets(curLine, sizeof(curLine), newFile)) {
        fputs(curLine, currentFile);
    }

    fclose(currentFile);
    fclose(newFile);
    remove(newPathToConfig);

    Log(Success, "Removed '%s' from your profile list.", profileName);

}