#include "global.h"
#include "utils.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void handler(int s) {
    if (s == SIGINT) {
        for (int i = 0; i < command_count; ++i) {
            if (commands[i].pid)
                kill(commands[i].pid, SIGINT);
        }
    }
}

int main(void) {
    init();
    signal(SIGINT, handler);
    char history_save_path[MAX_PATH_LEN];
    sprintf(history_save_path, "%s/.MyShell_history", home_directory);
    read_history(history_save_path);
    while (1) {
        char prefix[MAX_LEN];
        sprintf(prefix, "\001\033[""49"";""34""m\002[%s %s]$ \001\033[0m\002", user_string, displayed_directory);
        char* input = readline(prefix);
        if (!input) { puts("exit"); break; }
        if (strlen(input) == 0) continue;
        add_history(input);
        write_history(history_save_path);
        parse_command(input);
        //dump_command();
        if (command_count == 1) {
            if (!strlen(commands[0].input) && !strlen(commands[0].output))
                execute(commands);
            else {
                int pid = fork();
                if (pid == 0) {
                    redirect(commands);
                    execute(commands);
                    exit(1);
                }
                wait(NULL);
            }
        } 
        else {
            int pid = fork();
            if (pid == 0) {
                execute_pipe();
                exit(1);
            }
            wait(NULL);
        }
        for (int i = 0; i < command_count; ++i) {
            for (int j = 0; j < MAX_ARGC; ++j) {
                if (commands[i].argv[j]) {
                    free(commands[i].argv[j]);
                    commands[i].argv[j] = NULL;
                }
            }
        }
        command_count = 0;
        memset(commands, 0, sizeof(commands));
    }
    return 0;
}
