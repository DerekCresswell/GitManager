
#include <errno.h>
#include <linux/limits.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <tomlc99/toml.h>

#include <ArgContext.h>
#include <Commands/Commands.h>
#include <Logger.h>

toml_table_t* LoadConfigurationFile(const char* pathToConfig) {
    
    FILE* filePtr = fopen(pathToConfig, "r");
    if(!filePtr) {
        
        Log(Verbose, "No configuration file at : '%s'.", pathToConfig);
        Log(Verbose, "Creating new configuration file.");

        filePtr = fopen(pathToConfig, "w");

        if(!filePtr) {
            Log(Error, "Could not create file at : '%s'.", pathToConfig);
            return NULL;
        }

        fputs("# Gitmanager profile configuration.", filePtr);
        fputs("\nprofileNames = [\n]", filePtr);

        fclose(filePtr);
        filePtr = fopen(pathToConfig, "r");

    } else {

        Log(Verbose, "Found configuration file at : '%s'.", pathToConfig);

    }

    char errBuff[1024];
    toml_table_t* configurationFile = toml_parse_file(filePtr, errBuff,
        sizeof(errBuff));
    
    fclose(filePtr);

    if(!configurationFile) {
        Log(Error, "Error parsing configuration file.");
        return NULL;
    }

    return configurationFile;

}

/*
 * Usage : gitmanager <list|add|set> (options)
 */
int main(int argc, char* argv[]) {

    extern int optind;
    ArgContext* aContext = ParseArguments(argc, argv);
    InitLog(aContext);

    char cwdPath[PATH_MAX];
    if (getcwd(cwdPath, sizeof(cwdPath)) == NULL) {
       Log(Error, "Could not get the current working directory.");
       return 1;
    }

#ifdef __linux__

    char* userDirRoot = getpwuid(getuid())->pw_dir;
    const char* fileName = "/.gitmanager";
    char profilePath[strlen(userDirRoot) + strlen(fileName)];
    profilePath[0] = '\0';
    strcat(profilePath, strcat(userDirRoot, fileName));

#else
# error Only Linux is currently supported.
#endif

    toml_table_t* profileFile = LoadConfigurationFile(profilePath);

    if(strcmp(argv[optind], "list") == 0) {

        ListCommand(profileFile);

    } else if(strcmp(argv[optind], "add") == 0) {

    } else if(strcmp(argv[optind], "set") == 0) {

        if(argv[optind + 1] == NULL) {
            Log(Error, "The 'set' command requires a profile to be specified.");
            return 1;
        }

        SetCommand(profileFile, argv[optind + 1], cwdPath);

    } else {

        Log(Error, "'%s' is not a valid command.", argv[optind]);
        return 1;

    }

    return 0;

}