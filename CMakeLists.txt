cmake_minimum_required(VERSION 3.16)
project(comp_graf_project VERSION 0.1)

add_executable(comp_graf_project 
src/main.cpp
external/glad.c
external/glad.h
)

target_link_libraries(comp_graf_project glfw)
