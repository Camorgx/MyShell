#include "built_in.hpp"
#include "global.hpp"
#include "utils.hpp"

#include <string>
#include <unistd.h>
#include <cstdio>
#include <filesystem>

void cd(const std::string& dest) {
    std::string destination = dest.length() == 0 ? user_home_directory : dest;
    if (destination.starts_with("~"))
        destination = user_home_directory + destination.substr(1);
    try {
        destination = std::filesystem::canonical(
            std::filesystem::path(destination)).string();
    } 
    catch (std::filesystem::filesystem_error& e) {
        constexpr size_t pre_len = 
            std::string("filesystem error: cannot make canonical path: ").length();
        puts(e.what() + pre_len);
        return;
    }
    
    if (chdir(destination.c_str())) { perror("cd"); return; }
    current_working_directory = destination.starts_with(user_home_directory) ? 
        "~" + destination.substr(user_home_directory.length()) : destination;
}
