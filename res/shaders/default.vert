#version 330 core
layout (location = 0) in vec2 Position; // Vertex position

uniform vec2 Transformation; // Transformation

void main()
{
    gl_Position = vec4(Position + Transformation, 0.0 , 1.0); // Pass the vertex position to the fragment shader
}