cmake_minimum_required(VERSION 3.20)
project(MyShell)

set(CMAKE_C_STANDARD 17)

add_executable(MyShell src/main.c src/utils.c)

target_include_directories(MyShell
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(MyShell -lreadline)
