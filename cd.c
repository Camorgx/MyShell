#include "built_in.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

extern char* current_working_directory;
extern char* user_home_directory;

void cd(char* dest) {
    struct stat* state = (struct stat*) malloc(sizeof(struct stat));
    if (stat(dest, state) == -1) perror("cd");
    else if (!S_ISDIR(state->st_mode)) puts("cd: Not a directory");
    if (!current_working_directory) free(current_working_directory);
    current_working_directory = calloc(strlen(dest + 1), sizeof(char));
    if (!strcmp(user_home_directory, dest)) strcpy(current_working_directory, "~");
    else strcpy(current_working_directory, dest);
    free(state);
}