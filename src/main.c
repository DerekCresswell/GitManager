
#include <errno.h>
#include <linux/limits.h>
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
        Log(Error, "Error opening configuration file : '%s'.", pathToConfig);
        return NULL;
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

    ArgContext* aContext = ParseArguments(argc, argv);
    InitLog(aContext);

    char cwdPath[PATH_MAX];
    if (getcwd(cwdPath, sizeof(cwdPath)) == NULL) {
       Log(Error, "Could not get the current working directory.");
       return 1;
    }

    // Temp, will locate later
    const char* profilePath = "../test.toml";
    toml_table_t* profileFile = LoadConfigurationFile(profilePath);

    if(strcmp(argv[argc - 1], "list") == 0) {
        ListCommand(profileFile);
    } else if(strcmp(argv[argc - 1], "add") == 0) {

    } else if(strcmp(argv[argc - 1], "set") == 0) {
        SetCommand(profileFile, argv[2], cwdPath);
    } else {
        Log(Error, "\"%s\" is not a valid command.", argv[argc - 1]);
        return 1;
    }

    return 0;

}