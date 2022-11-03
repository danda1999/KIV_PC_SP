cmake_minimum_required(VERSION 3.10)

project(qsortdemo LANGUAGES C)
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic -ansi")

add_executable(qsortdemo
    src/qsortdemo.c
)
