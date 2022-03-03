#include "built_in.h"

#include <stdlib.h>
#include <string.h>

extern char* current_working_directory;
extern char* user_home_directory;

void cd(char* dest) {
    if (!current_working_directory) free(current_working_directory);
    current_working_directory = calloc(strlen(dest + 1), sizeof(char));
    if (!strcmp(user_home_directory, dest)) strcpy(current_working_directory, "~");
    else strcpy(current_working_directory, dest);
}