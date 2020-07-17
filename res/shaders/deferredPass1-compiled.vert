#version 330 core
#define GLSLIFY 1

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texCoords0;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

out vec2 texCoords0ToFrag;

void main()
{
    gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
    texCoords0ToFrag = texCoords0;
}