#ifndef SIMPLE_SHELL_UTILS_H
#define SIMPLE_SHELL_UTILS_H

#include <string>
#include <vector>

std::vector<std::string> string_split(const std::string& source);

void handle_input(const std::string& input);

void exec_redirection(const std::vector<std::string>& argv);

#endif //SIMPLE_SHELL_UTILS_H
