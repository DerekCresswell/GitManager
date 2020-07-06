
#include <stdio.h>
#include <string.h>

#include "Profile.h"

Profile* LoadProfiles(const char* pathToProfiles) {

    FILE* filePtr = fopen(pathToProfiles, "r");

    char errBuff[1024];

    toml_table_t* configurationFile = toml_parse_file(filePtr, errBuff, sizeof(errBuff));

    const char** profileNames;
    LoadProfileNames(configurationFile, profileNames);

}

int LoadProfileNames(toml_table_t* table, const char* buffer[]) {

    toml_array_t* profileNames = toml_array_in(table, "profileNames");
    int nElms = toml_array_nelem(profileNames);

    for(int i = 0; i < nElms; i++) {

        const char* nameAct = toml_raw_at(profileNames, i);
        char* nameFormatted;
        if(toml_rtos(nameAct, &nameFormatted) == 0) {
            buffer[i] = nameFormatted;
        }

    }

    return nElms;

}

void AddProfile(const char* profileName) {



}

void RemoveProfile(Profile* profile) {



}

void SetProfileOnRepo(Profile* profile, const char* pathToRepo) {



}

// Helpers

Profile* NameToProfile(const char* name) {



}