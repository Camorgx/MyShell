#ifndef SIMPLE_SHELL_UTILS_H
#define SIMPLE_SHELL_UTILS_H

void full_path(char* dest);

char** split(const char* line);

int handle_input(char* input);

#endif //SIMPLE_SHELL_UTILS_H