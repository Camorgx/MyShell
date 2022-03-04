#include "utils.h"
#include "built_in.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int handle_input(char* input) {
    char** input_split = split(input);
    if (!strcmp(input_split[0], "cd")) cd(input_split[1]);
    else if (!strcmp(input_split[0], "history")) history();
    else {
        pid_t pid = fork();
        int status;
        if (pid == 0 && execvp(input_split[0], input_split)
            || pid < 0) perror("Error");
        else do waitpid(pid, &status, WUNTRACED);
        while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    free(input_split);
}