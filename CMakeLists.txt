cmake_minimum_required(VERSION 3.23)
project(TestLab3 C)

set(CMAKE_C_STANDARD 99)

add_executable(TestLab3 main.c bmp.h save.c read.c image.h tarnsform.h transform.c)
