cmake_minimum_required(VERSION 3.10)
project(Cpp_Opengl_Game)

set(OpenGL_GL_PREFERENCE GLVND)
# Find required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(PNG REQUIRED)
find_package(Freetype REQUIRED)
find_package(HarfBuzz REQUIRED)

# Add executable
add_executable(main
        src/main.cpp

        src/engine/Engine.cpp
        src/engine/Application.cpp
        src/engine/Initialization.cpp
        src/engine/Window.cpp
        src/engine/Renderer.cpp
        src/engine/EventManager.cpp

        src/graphics/Shader.cpp
        src/graphics/BatchColored.cpp
        src/graphics/BatchTextured.cpp
        src/graphics/ModelLoader.cpp
        src/graphics/Text.cpp
        src/graphics/FontRenderer.cpp

        src/utils/Logger.cpp

        src/gameobjects/Rectangle.cpp
        src/gameobjects/Camera.cpp

        src/game/Game.cpp
        src/game/CameraController.cpp
        )

# Add include directory
target_include_directories(main PRIVATE
        include
        vendor
        vendor/FREETYPE
        )

# Link libraries
target_link_libraries(main
        OpenGL::GL
        glfw
        GLEW::GLEW
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/Linux/libsoil2.a
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/Linux/libfreetype.a
        harfbuzz
        brotlidec
        bz2
        PNG::PNG
        )
