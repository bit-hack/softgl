cmake_minimum_required(VERSION 3.0)
project(opengl32)

file(GLOB C_FILES source/*.cpp)
file(GLOB H_FILES source/*.h)

add_library(opengl32 SHARED ${C_FILES} ${H_FILES} opengl32.def)
