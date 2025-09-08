cmake_minimum_required(VERSION 3.16)
project(comp_graf_project VERSION 0.1)

file(GLOB SRC_FILES
    src/*.cpp
    external/glad/src/glad.c
)

include_directories( SYSTEM "external/glad/include" )

add_executable(comp_graf_project 
    src/main.cpp
    src/shader.cpp
    src/triangle.cpp
    src/error.cpp
    external/glad/src/glad.c
)

add_custom_command(TARGET comp_graf_project POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_SOURCE_DIR}/src/shaders
          $<TARGET_FILE_DIR:comp_graf_project>/shaders
)

target_link_libraries(comp_graf_project glfw)
