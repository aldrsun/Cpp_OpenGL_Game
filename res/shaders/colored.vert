#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;

out vec4 ColorData;

uniform mat4 u_Transformation;

void main()
{
    ColorData = aColor;
    gl_Position = u_Transformation * vec4(aPosition, 1.0);
}