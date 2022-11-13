cmake_minimum_required(VERSION 3.23)
project(nagyhazi C)

set(CMAKE_C_STANDARD 99)

add_executable(nagyhazi main.c value_checks.c value_checks.h)
