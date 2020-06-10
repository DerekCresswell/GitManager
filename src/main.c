
#include <errno.h>
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <tomlc99/toml.h>

#include <Commands/Commands.h>

toml_table_t* LoadConfigurationFile(const char* pathToConfig) {
    
    FILE* filePtr = fopen(pathToConfig, "r");
    if(!filePtr) {
        printf("Error opening figuration file : %s\n", pathToConfig);
        return NULL;
    }

    char errBuff[1024];
    toml_table_t* configurationFile = toml_parse_file(filePtr, errBuff,
        sizeof(errBuff));
    
    fclose(filePtr);

    if(!configurationFile) {
        printf("Error parsing configuration file\n");
        return NULL;
    }

    return configurationFile;

}

/*
 * Usage : gitmanager <list|add|set> (options)
 * 
 * Look into getopt
 */
int main(int argc, char* argv[]) {

    if(argc < 2) {

        printf("Error : No arguments given.\n");
        return 1;
    }

    char cwdPath[PATH_MAX];
    if (getcwd(cwdPath, sizeof(cwdPath)) == NULL) {
       printf("Could not get the current working directory.\n");
       return 1;
    }

    // Temp, will locate later
    const char* configPath = "../test.toml";
    toml_table_t* configFile = LoadConfigurationFile(configPath);
    if(!configFile) {
        return 1;
    }

    if(strcmp(argv[1], "list") == 0) {
        ListCommand(configFile);
    } else if(strcmp(argv[1], "add") == 0) {

    } else if(strcmp(argv[1], "set") == 0) {
        SetCommand(configFile, argv[2], cwdPath);
    } else {
        printf("\"%s\" is not a valid command.\n", argv[1]);
        return 1;
    }

    return 0;

}