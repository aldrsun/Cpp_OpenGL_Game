#version 330 core
out vec4 FragColor;

in vec4 ColorData;

void main()
{
    FragColor = ColorData;
}