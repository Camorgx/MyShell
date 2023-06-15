#include "global.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    char input[MAX_LEN];
    init();
    while (1) {
        char prefix[MAX_LEN];
        sprintf(prefix, "[%s %s]", user_string, displayed_directory);
        printf("%s >>> ", prefix);
        fgets(input, MAX_LEN, stdin);
        input[strlen(input) - 1] = '\0';
        if (strlen(input) == 0) continue;
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