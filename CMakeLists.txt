cmake_minimum_required(VERSION 3.20)
project(Simple_Shell)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

add_executable(Simple_Shell
        src/main.cpp src/user_string.cpp src/global.cpp
        src/init_wd.cpp src/cd.cpp src/split.cpp
        src/history.cpp src/handle_input.cpp)

target_include_directories(Simple_Shell
PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(Simple_Shell -lreadline)
