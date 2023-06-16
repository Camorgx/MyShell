#include "builtins.h"
#include "global.h"
#include "utils.h"

#include <fcntl.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void parse_command(char* line) {
    char *tokens;
    char *buf1 = NULL;
    tokens = strtok_r(line, "|", &buf1);
    while (tokens) {
        parse_argv(tokens, command_count);
        ++command_count;
        if (command_count > 2) {
            puts("Error: we only support using pipe with two processes.");
            return;
        }
        tokens = strtok_r(NULL, "|", &buf1);
    }
}

void parse_argv(char* line, int command_count) {
    char buffer[MAX_LEN];
    memset(buffer, 0, sizeof(buffer));
    strcpy(buffer, line);
    int count = 0;
    char* token;
    char* buf;
    token = strtok_r(buffer, " ", &buf);
    while (token) {
        if (strchr(token, '<')) {
            if (strlen(token) > 1) {
                strcpy(commands[command_count].input, token + 1);
                token = strtok_r(NULL, " ", &buf);
                continue;
            } 
            else {
                token = strtok_r(NULL, " ", &buf);
                strcpy(commands[command_count].input, token);
                token = strtok_r(NULL, " ", &buf);
                continue;
            }
        }
        if (strchr(token, '>')) {
            if (strlen(token) > 1) {
                strcpy(commands[command_count].output, token + 1);
                token = strtok_r(NULL, " ", &buf);
                continue;
            } 
            else {
                token = strtok_r(NULL, " ", &buf);
                strcpy(commands[command_count].output, token);
                token = strtok_r(NULL, " ", &buf);
                continue;
            }
        }
        if (token) {
            commands[command_count].argv[count] = (char*)malloc(MAX_LEN);
            strcpy(commands[command_count].argv[count], token);
        }
        count++;
        token = strtok_r(NULL, " ", &buf);
    }
    commands[command_count].argv[count] = NULL;
    commands[command_count].argc = count;
}

void redirect(command* c) {
    int fd1 = open(c->output, O_CREAT | O_RDWR, 0666);
    dup2(fd1, 1);
    close(fd1);
    int fd0 = open(c->input, O_CREAT | O_RDWR, 0666);
    dup2(fd0, 0);
    close(fd0);
}

void execute(command *c) {
    if (strcmp(c->argv[0], "exit") == 0) exit(0);
    else if (strcmp(c->argv[0], "pwd") == 0) pwd();
    else if (strcmp(c->argv[0], "cd") == 0) cd(c->argv[1]);
    else {
        int pid = fork();
        if (pid == 0) {
            if (execvp(c->argv[0], c->argv) < 0)
                perror("execvp");
            exit(0);
        }
        c->pid = pid;
        wait(NULL);
    }
}

void execute_pipe(void) {
	int pid, fd[2];
    pipe(fd); 
    pid = fork();
    if (pid == 0) { 
        dup2(fd[0], 0); 
        close(fd[0]);
        close(fd[1]);
        execute(commands + 1);
        exit(0);
    }
    dup2(fd[1], 1); 
    close(fd[0]);
    close(fd[1]);
    execute(commands);
}

void init(void) {
    struct passwd* usr = getpwuid(getuid());
    strcpy(user_string, usr->pw_name);
    strcpy(home_directory, usr->pw_dir);
    char host_buffer[MAX_LEN];
    gethostname(host_buffer, sizeof(host_buffer));
    strcat(user_string, "@");
    strcat(user_string, host_buffer);
    update_display_dir();
}

void update_display_dir() {
    char tmp[MAX_PATH_LEN];
    getcwd(tmp, sizeof(tmp));
    if (strncmp(tmp, home_directory, strlen(home_directory)) == 0) {
        strcpy(displayed_directory, "~");
        strcat(displayed_directory, tmp + strlen(home_directory));
    }
}
