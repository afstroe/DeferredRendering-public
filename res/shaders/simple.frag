#version 330 core

in vec3 vertexColor;

// output
layout (location = 0) out vec4 color;

void main()
{
  color = vec4(vertexColor, 1.0);
}