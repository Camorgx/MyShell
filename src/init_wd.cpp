#include "global.hpp"

#include <filesystem>
#include <string>

std::string init_wd() {
    auto currentPath = std::filesystem::current_path().string();
    if (currentPath.starts_with(user_home_directory))
        currentPath = "~" + currentPath.substr(user_home_directory.length());
    return currentPath;
}
