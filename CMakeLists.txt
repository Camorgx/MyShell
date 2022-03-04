cmake_minimum_required(VERSION 3.20)
project(Simple_Shell)

set(CMAKE_C_STANDARD 17)

add_executable(Simple_Shell
        src/main.c src/user_string.c
        src/init_wd.c src/cd.c src/split.c
        src/history.c src/full_path.c src/handle_input.c)

target_include_directories(Simple_Shell
PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(Simple_Shell -lreadline)