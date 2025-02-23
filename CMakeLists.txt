cmake_minimum_required(VERSION 3.10)
project(Cpp_Opengl_Game)

set(OpenGL_GL_PREFERENCE GLVND)
# Find required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

# Add executable
add_executable(main
        src/main.cpp

        src/engine/Engine.cpp
        src/engine/Application.cpp
        src/engine/Initialization.cpp
        src/engine/Renderer.cpp

        src/graphics/Shader.cpp
        src/graphics/Mesh.cpp
        src/graphics/MeshStatic.cpp
        src/graphics/MeshDynamic.cpp
        
        src/utils/Logger.cpp
        
        src/game/Game.cpp
        
        src/gameobjects/singleobjects/Triangular.cpp)

# Add include directory
target_include_directories(main PRIVATE include)

# Link libraries
target_link_libraries(main OpenGL::GL glfw GLEW::GLEW)