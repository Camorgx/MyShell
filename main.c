#include "init.h"

#include <stdio.h>

char *user_home_directory, *current_working_directory;
char *user_name, *host_name;
int is_root;

int main(int argc, const char** argv) {
    char* user_str = user_string();
    char input_line[256];
    current_working_directory = init_wd();
    while (1) {
        printf("[%s%s]%s", user_str, current_working_directory, is_root ? "# " : "$ ");
        if (!fgets(input_line, 256, stdin)) {
            puts("\nexit");
            break;
        }
    }
    return 0;
}