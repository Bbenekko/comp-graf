cmake_minimum_required(VERSION 3.16)
project(comp_graf_project VERSION 0.1)

file(GLOB SRC_FILES
    src/*.cpp
    external/glad/src/glad.c
)

include_directories( SYSTEM "external/glad/include" "external/stb" )

add_executable(comp_graf_project 
    src/main_2d.cpp
    src/shader.cpp
    src/triangle.cpp
    src/polygon.cpp
    src/circle.cpp
    src/line.cpp
    src/error.cpp
    src/camera2d.cpp
    src/transform.cpp
    src/state.cpp
    src/scene.cpp
    src/node.cpp
    src/quad.cpp
    src/grid.cpp
    src/arcball.cpp
    src/color.cpp
    src/computeshader.cpp
    src/cube.cpp
    src/framebuffer.cpp
    src/image.cpp
    src/light.cpp
    src/material.cpp
    #src/main_gpgpu.cpp
    src/mesh.cpp
    src/polyoffset.cpp
    src/sphere.cpp
    src/texbuffer.cpp
    src/texcube.cpp
    src/texdepth.cpp
    src/texture.cpp

    external/glad/src/glad.c
)

add_custom_command(TARGET comp_graf_project POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_SOURCE_DIR}/src/shaders
          $<TARGET_FILE_DIR:comp_graf_project>/shaders
)

target_link_libraries(comp_graf_project glfw)
