#include "utils.hpp"
#include "built_in.hpp"

#include <cstdio>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void handle_input(const std::string& input) {
    if (input.length() == 0) return;
    auto input_split =  string_split(input);
    if (input_split[0] == "cd") 
        cd(input_split.size() > 1 ? input_split[1] : "");
    else if (input_split[0] == "history") history();
    else if (input_split[0] == "exit") exit(0);
    else {
        std::vector<std::vector<std::string>> split;
        int start_pos = 0;
        size_t size  = input_split.size();
        for (int i = 0; i < size; ++i) {
            if (input_split[i] == "|") {
                split.emplace_back();
                for (int j = start_pos; j < i; ++j)
                    split.back().emplace_back(input_split[j]);
                start_pos = i + 1;
            }
        }
        if (start_pos != size - 1) {
            split.emplace_back();
            for (int i = start_pos; i < size; ++i)
                split.back().emplace_back(input_split[i]);
        }
        exec_redirection(input_split);
    }
}

#include <cstring>
#include <iostream>
#include <filesystem>
#include <unordered_set>

void exec_redirection(const std::vector<std::string>& argv) {
    int in_pos = -1, in_cnt = 0;
    int out_pos = -1, out_cnt = 0;
    int argc = static_cast<int>(argv.size());
    for (int i = 0; i < argc; ++i) {
        if (argv[i] == "<") {
            in_pos = i;
            ++in_cnt;
        }
        else if (argv[i] == ">" || argv[i] == ">>") {
            out_pos = i;
            ++out_cnt;
        }
    }
    if (in_cnt > 1 || out_cnt > 1) {
        std::cerr << "Error: Too many redirection operator.\n";
        return;
    }
    if (in_pos == argc - 1 || out_pos == argc - 1) {
        std::cerr << "Error: Missing redirection file.\n";
        return;
    }
    if (in_cnt && !std::filesystem::exists(argv[in_pos + 1])) {
        std::cerr << "Error: Input file not exist.\n";
        return;
    }
    char** new_argv = new char*[argc + 1];
    int p = 0;
    std::unordered_set<std::string> red = { ">", ">>", "<", "<<" };
    for (int i = 0; i < argc; ++i) {
        if ((argv[i] == "0" || argv[i] == "1" || argv[i] == "2") &&
            (i < argc - 1 && red.find(argv[i + 1]) != red.end())) i += 2;
        else if (i == in_pos || i == out_pos) ++i;
        else {
            new_argv[p] = new char[argv[i].length() + 1];
            std::strncpy(new_argv[p++], argv[i].c_str(), argv[i].length());
        }
    }
    new_argv[p] = nullptr;
    pid_t pid = vfork();
    if (pid < 0) perror("Error: ");
    else if (pid == 0) {
        int in_stream = 0;
        if (in_cnt) {
            if (argv[in_pos - 1] == "1") in_stream = 1;
            else if (argv[in_pos - 1] == "2") in_stream = 2;
        }
        int out_stream = 1;
        if (out_cnt) {
            if (argv[out_pos - 1] == "0") out_stream = 0;
            else if (argv[out_pos - 1] == "2") out_stream = 2;
        }
        int in_fd;
        if (in_cnt) {
            close(in_stream);
            int fd = open(argv[in_pos + 1].c_str(),
                O_RDONLY, 0777);
            in_fd = dup2(in_stream, fd);
        }
        int out_fd;
        if (out_cnt) {
            close(out_stream);
            int fd = open(argv[out_pos + 1].c_str(), 
                argv[out_pos] == ">" ? (O_WRONLY | O_CREAT) 
                    : (O_APPEND | O_WRONLY | O_CREAT), 
                0777);
            out_fd = dup2(out_stream, fd);
        }
        execvp(new_argv[0], new_argv);
        if (out_cnt) {
            dup2(out_fd, out_stream);
            dup2(in_fd, in_stream);
        }
        exit(1);
    }
    else {
        int status;
        waitpid(pid, &status, 0);
    }
}
