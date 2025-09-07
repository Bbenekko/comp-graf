cmake_minimum_required(VERSION 3.16)
project(triangle)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -DGL_SILENCE_DEPRECATION")

set(SRC_FILES error.cpp shader.cpp triangle.cpp main.cpp ${OPENGL_gl_LIBRARY})

include_directories(. /opt/homebrew/include)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(assimp REQUIRED)

add_executable(t ${SRC_FILES})

target_include_directories(t PRIVATE ${OPENGL_INCLUDE_DIR})

target_link_libraries(t OpenGL::GL glfw assimp)

target_compile_definitions(t PRIVATE GL_GLEXT_PROTOTYPES)

message(STATUS "OpenGL Found: ${OPENGL_FOUND}")
message(STATUS "GLFW3 Found: ${glfw3_FOUND}")
message(STATUS "Assimp Found: ${assimp_FOUND}")
