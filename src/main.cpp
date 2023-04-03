#include "init.hpp"
#include "global.hpp"
#include "utils.hpp"

#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <fmt/format.h>
#include <string>

#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, const char** argv) {
    std::string user_str = user_string();
    char line_head[256];
    current_working_directory = init_wd();
    char history_save_path[256];
    sprintf(history_save_path, "%s/.simple_shell_history", user_home_directory.c_str());
    read_history(history_save_path);
    while (true) {
        sprintf(line_head, "\001\033[""49"";""34""m\002[%s %s]%s\001\033[0m\002",
                user_str.c_str(), current_working_directory.c_str(), is_root ? "# " : "$ ");
        char* input_line = readline(line_head);
        if (!input_line) { puts("exit"); exit(0); }
        if (std::strlen(input_line)) add_history(input_line);
        write_history(history_save_path);
        handle_input(input_line);
    }
    return 0;
}
