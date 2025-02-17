cmake_minimum_required(VERSION 3.10)
project(Cpp_Opengl_Game)

set(OpenGL_GL_PREFERENCE GLVND)
# Find required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

# Add executable
add_executable(main src/main.cpp
        src/engine/core/Engine.cpp
        src/engine/core/Engine.h
        src/engine/core/Initialization.cpp
        src/engine/core/Initialization.h
        src/engine/graphics/Shader.cpp
        src/engine/graphics/Shader.h
        src/engine/graphics/MeshStatic.cpp
        src/engine/graphics/MeshStatic.h
        src/engine/graphics/MeshDynamic.cpp
        src/engine/graphics/MeshDynamic.h
        src/engine/utils/Logger.cpp
        src/engine/utils/Logger.h
        src/game/Application.cpp
        src/game/Application.h)

# Link libraries
target_link_libraries(main OpenGL::GL glfw GLEW::GLEW)