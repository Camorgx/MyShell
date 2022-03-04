#include "init.h"

#include <string.h>
#include <stdlib.h>

extern char* current_working_directory;
extern char* user_home_directory;

char* display_directory() {
    char* dd = (char*) calloc(strlen(current_working_directory), sizeof(char));
    strncpy(dd, current_working_directory, strlen(user_home_directory));
    if (!strcmp(dd, user_home_directory)) {
        dd[0] = '~';
        strcpy(dd + 1, current_working_directory + strlen(user_home_directory));
        return dd;
    }
    else {
        strcpy(dd, current_working_directory);
        return dd;
    }
}