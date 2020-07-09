
#ifndef PROFILE_H
#define PROFILE_H

#include <tomlc99/toml.h>

#define MAX_PROFILE_NAME_SIZE 32

struct Profile {
    char* profileName;
    char* description;

    // Git data
    char* userName;
    char* email;
};
typedef struct Profile Profile;

Profile* LoadProfiles(const char* pathToProfiles);

int LoadProfileNames(toml_table_t* table, const char* buffer[]);

void AddProfile(const char* profileName);

void RemoveProfile(Profile* profile);

void SetProfileOnRepo(Profile* profile, const char* pathToRepo);

// Helpers

Profile* NameToProfile(const char* name);

#endif