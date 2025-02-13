#version 330 core
out vec4 FragColor; // Output color

in vec4 ColorData;

void main()
{
    FragColor = ColorData;
}