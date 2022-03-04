#include "init.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

char *user_home_directory, *current_working_directory;
char *user_name, *host_name;
int is_root;

int main(int argc, const char** argv) {
    char* user_str = user_string();
    char line_head[256];
    current_working_directory = init_wd();
    char history_save_path[256];
    sprintf(history_save_path, "%s/.simple_shell_history", user_home_directory);
    read_history(history_save_path);
    while (1) {
        sprintf(line_head, "\001\033[""49"";""34""m\002[%s%s]%s\001\033[0m\002",
                user_str, current_working_directory, is_root ? "# " : "$ ");
        char* input_line = readline(line_head);
        if (!input_line) { puts("exit"); break; }
        add_history(input_line);
        write_history(history_save_path);
        handle_input(input_line);
        free(input_line);
    }
    return 0;
}