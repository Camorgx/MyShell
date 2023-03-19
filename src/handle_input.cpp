#include "utils.hpp"
#include "built_in.hpp"

#include <cstddef>
#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>

void handle_input(const std::string& input) {
    if (input.length() == 0) return;
    auto input_split =  string_split(input);
    if (input_split[0] == "cd") cd(input_split[1]);
    else if (input_split[0] == "history") history();
    else if (input_split[0] == "exit") exit(0);
    else {
        int size = input_split.size();
        char** argv = new char*[size + 1];
        for (int i = 0; i < size; ++i)
            argv[i] = const_cast<char*>(input_split[i].c_str());
        argv[size] = nullptr;
        pid_t pid = fork();
        int status;
        if (pid < 0) perror("Error");
        else if (pid == 0 && execvp(input_split[0].c_str(), argv)) {
            perror("Execution error");
            exit(1);
        }
        else do waitpid(pid, &status, WUNTRACED);
        while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}
