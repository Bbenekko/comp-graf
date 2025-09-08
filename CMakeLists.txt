cmake_minimum_required(VERSION 3.16)
project(comp_graf_project VERSION 0.1)

include_directories( SYSTEM "external/glad/include" )

add_executable(comp_graf_project 
src/teste.cpp
external/glad/src/glad.c
external/glad/include/glad/glad.h
)

target_link_libraries(comp_graf_project glfw)
