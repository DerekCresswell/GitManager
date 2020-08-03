
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Input.h"

char* GetUserString(const char* prompt, int maxSize) {

    printf("%s : ", prompt);
    char userIn[maxSize];

    fgets(userIn, sizeof(userIn), stdin);

    userIn[strcspn(userIn, "\n")] = 0;

    char* allocString = malloc(maxSize * sizeof(char));
    strcpy(allocString, userIn);

    return allocString;

}