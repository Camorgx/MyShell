#pragma once

#define MAX_LEN 1024
#define MAX_ARGC 16
#define MAX_PATH_LEN 1024

typedef struct command{
	int argc;
	int pid;
	int job_id;
	char* argv[MAX_ARGC];
	char input[MAX_LEN];
	char output[MAX_LEN];
} command;

extern int command_count;

extern command commands[4];

// not with last '/'
extern char home_directory[MAX_PATH_LEN];

extern char displayed_directory[MAX_PATH_LEN];

extern char user_string[MAX_LEN];
