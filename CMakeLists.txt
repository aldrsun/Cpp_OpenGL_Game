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
	src/engine/EventManager.cpp

        src/graphics/Shader.cpp
        src/graphics/BatchColored.cpp
        src/graphics/BatchTextured.cpp

        src/utils/Logger.cpp
        
        src/game/Game.cpp
        
	src/gameobjects/Rectangle.cpp
        src/gameobjects/Camera.cpp
        )

# Add include directory
target_include_directories(main PRIVATE include vendor)

# Link libraries
target_link_libraries(main OpenGL::GL glfw GLEW::GLEW ${CMAKE_CURRENT_SOURCE_DIR}/lib/Linux/libsoil2.a)
