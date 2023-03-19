#include "init.hpp"
#include "global.hpp"

#include <unistd.h>
#include <pwd.h>

#include <string>
#include <fmt/format.h>

std::string user_string() {
    struct passwd* usr = getpwuid(getuid());
    user_name = usr->pw_name;
    user_home_directory = usr->pw_dir;
    is_root = "root" == user_name;
    size_t buffer_size = 20;
    char* host_buffer = new char[buffer_size];
    while (gethostname(host_buffer, buffer_size) == -1) {
        buffer_size <<= 1;
        delete[] host_buffer;
        host_buffer = new char[buffer_size];
    }
    std::string host_name(host_buffer);
    delete[] host_buffer;
    return fmt::format("{}@{}", user_name, host_name);
}
