
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include <Input.h>
#include <Logger.h>
#include <Profile/Profile.h>

#include "Add.h"

void ValidateProfileName(char* name) {

    int nameLength = strlen(name);
    if(nameLength > MAX_PROFILE_NAME_SIZE) {
        Log(Error, "Profile names must be less than %d. The given name is %d characters long.",
            MAX_PROFILE_NAME_SIZE, nameLength);
        return;
    }

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

void AddKeyToFile(FILE* fp, const char* key, const char* value) {

    fputs(key, fp);
    fputs(" = \"", fp);
    fputs(value, fp);
    fputs("\"\n", fp);

}

int AddCommand(toml_table_t* configFile, char* profileName, const char* pathToConfig) {

    const char* nameBuffer[MAX_PROFILE_NAME_SIZE];
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
    strcpy(newPathToConfig, pathToConfig);
    strcat(newPathToConfig, tempSuffix);

    FILE* newFile = fopen(newPathToConfig, "w");
    if(!newFile) {
        Log(Error, "Could not create file '%s'.", newPathToConfig);
        return 0;
    }
    Log(Verbose, "Opened temporary file at '%s'.", newPathToConfig);

    // Copy the current file to a temporary one.
    char curLine[256];
    int watchForCloseTag = 0;
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

        if(strcmp(modLine, "profileNames = [\n") == 0) {
            watchForCloseTag = 1;
        }

        if(watchForCloseTag && strcmp(modLine, "]\n") == 0) {
            fputs("\t\"", newFile);
            fputs(profileName, newFile);
            fputs("\",\n", newFile);
        }

        fputs(curLine, newFile);

    }

    fclose(currentFile);

    fputs("\n[", newFile);
    fputs(profileName, newFile);
    fputs("]\n", newFile);

    char* input = GetUserString("Enter the user name", 64);
    AddKeyToFile(newFile, "userName", input);
    free(input);

    input = GetUserString("Enter the user email", 64);
    AddKeyToFile(newFile, "userEmail", input);
    free(input);

    input = GetUserString("Enter the profile description (blank for none)", 256);
    if(strlen(input) != 0) {
        AddKeyToFile(newFile, "description", input);
    }
    free(input);

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

    Log(Success, "Added '%s' to your profile list.", profileName);

}