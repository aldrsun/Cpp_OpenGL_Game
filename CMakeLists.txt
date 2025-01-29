cmake_minimum_required(VERSION 3.10)
project(OpenGL_Snake_Game)

set(OpenGL_GL_PREFERENCE GLVND)
# Find required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

# Add executable
add_executable(main src/main.cpp
        src/core/Application.cpp
        src/core/Application.h
        src/graphics/Shader.cpp
        src/graphics/Shader.h
        src/graphics/Mesh.cpp
        src/graphics/Mesh.h
        src/utils/Logger.cpp
        src/utils/Logger.h)

# Link libraries
target_link_libraries(main ${OPENGL_LIBRARIES} glfw GLEW::GLEW)