#pragma once

#include "global.h"

// execute command without redirection or pipe
extern void execute(command *c); 	

// create pipe and execute command with execute()
extern void execute_pipe(void);   	

// handle redirection command
extern void redirect(command *c);

// parse pipe command
extern void parse_command(char *line);    

// parse argv of commands
extern void parse_argv(char *line,int c_count); 

extern void init(void);

extern void update_display_dir(void);
