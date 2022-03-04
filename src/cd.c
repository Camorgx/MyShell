#include "built_in.h"
#include "utils.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

extern char* current_working_directory;
extern char* user_home_directory;

void cd(char* dest) {
    if (!dest) {
        strcpy(current_working_directory, user_home_directory);
        if (chdir(user_home_directory)) perror("cd");
        return;
    }
    full_path(dest);
    if (chdir(dest)) { perror("cd"); return; }
    if (!current_working_directory) free(current_working_directory);
    current_working_directory = (char*) calloc(strlen(dest + 1), sizeof(char));
    strcpy(current_working_directory, dest);
}