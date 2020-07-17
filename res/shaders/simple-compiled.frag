#version 330 core
#define GLSLIFY 1

in vec3 vertexColor;

// output
layout (location = 0) out vec4 color;

void main()
{
  color = vec4(vertexColor, 1.0);
}