#define MAX_LEN 1024
#define MAX_ARGC 16

typedef struct command{
	int argc;
	char* argv[MAX_ARGC];
	char input[MAX_LEN];
	char output[MAX_LEN];
} command;

// execute command without redirection or pipe
void execute(command *c); 	

// create pipe and execute command with execute()
void execute_pipe();   	

// handle redirection command
void redirect(command *c);

// parse pipe command
void parse_command(char *line);    

// parse argv of commands
void parse_argv(char *line,int c_count); 

extern int command_count;
extern command commands[4];
