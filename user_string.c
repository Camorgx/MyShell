#include "init.h"

#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern char* user_home_directory;
extern char* user_name;
extern int is_root;
extern char* host_name;

char* user_string() {
    struct passwd* usr = getpwuid(getuid());
    user_name = usr->pw_name;
    user_home_directory = usr->pw_dir;
    if (strcmp("root", usr->pw_name) == 0) is_root = 1;
    host_name = (char*) calloc(20, sizeof(char));
    int buffer_size = 20;
    while (gethostname(host_name, buffer_size) == -1) {
        buffer_size <<= 1;
        reallocarray(host_name, buffer_size, sizeof(char));
    }
    char* ans = (char*) calloc(strlen(usr->pw_name) + strlen(host_name) + 10,
                               sizeof(char));
    sprintf(ans, "%s@%s ", usr->pw_name, host_name);
    return ans;
}
