#version 330 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;

out vec2 vTexCoord;

uniform vec3 Transformation;

void main() {
    gl_Position = vec4(Transformation + aPosition, 1.0);
    vTexCoord = aTexCoord;
}