#include "init.h"

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

extern char* user_home_directory;

char* init_wd() {
    int buffer_size = 20;
    char* buffer = (char*) calloc(20, sizeof(char));
    while (!getcwd(buffer, buffer_size)) {
        buffer_size <<= 1;
        buffer = reallocarray(buffer, buffer_size, sizeof(char));
    }
    if (!strcmp(user_home_directory, buffer)) return "~";
    return buffer;
}