cmake_minimum_required(VERSION 3.5)

project(loader LANGUAGES C)
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic -ansi")

add_executable(loader
    src/loader.c
    src/vector.c
    src/person.c
)
