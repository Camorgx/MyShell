cmake_minimum_required(VERSION 3.20)
project(Simple_Shell)

set(CMAKE_C_STANDARD 11)

add_executable(Simple_Shell main.c user_string.c init_wd.c cd.c history.c full_path.c)

target_link_libraries(Simple_Shell -lreadline)