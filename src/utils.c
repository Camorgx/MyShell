#include "utils.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int command_count = 0;

void parse_command(char* line) {
    char *tokens;
    char *buf1 = NULL;
    tokens = strtok_r(line, "|", &buf1);
    while (tokens) {
        parse_argv(tokens, command_count);
        ++command_count;
        tokens = strtok_r(NULL, "|", &buf1);
    }
}

command commands[4];

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
    else if (strcmp(c->argv[0], "pwd") == 0) {
        char path_name[100];
        if (getcwd(path_name, sizeof(path_name)))
            puts(path_name);
    } 
    else if (strcmp(c->argv[0], "cd") == 0) {
        chdir(c->argv[1]);
    } 
    else {
        int pid = fork();
        if (pid == 0) {
            if (execvp(c->argv[0], c->argv) < 0)
                perror("execvp");
            exit(0);
        }
        wait(NULL);
    }
}

void execute_pipe() {
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
