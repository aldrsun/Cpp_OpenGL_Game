#version 330 core
layout (location = 0) in vec3 Position; // Vertex position
layout (location = 1) in vec4 Color; // Vertex position

out vec4 ColorData;

uniform vec3 Transformation; // Transformation

void main()
{
    ColorData = Color;
    gl_Position = vec4(Position/* + Transformation*/, 1.0); // Pass the vertex position to the fragment shader
}