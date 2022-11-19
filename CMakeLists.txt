cmake_minimum_required(VERSION 3.23)
project(nagyhazi C)

set(CMAKE_C_STANDARD 99)

add_executable(nagyhazi main.c value_checks.c value_checks.h matrix_io.c matrix_io.h line_operations.c line_operations.h matrix_operations.c matrix_operations.h value_check.c value_check.h matrix_lib.c matrix_lib.h)
