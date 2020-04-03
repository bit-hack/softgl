cmake_minimum_required(VERSION 3.0)
project(opengl32)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

add_subdirectory(rast_fasterizer)
add_subdirectory(rast_wireframe)
add_subdirectory(rast_reference)

file(GLOB C_FILES source/*.cpp)
file(GLOB H_FILES source/*.h)

add_library(opengl32 SHARED ${C_FILES} ${H_FILES} opengl32.def)
