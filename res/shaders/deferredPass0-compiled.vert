#version 330 core
#define GLSLIFY 1

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords0;

uniform vec3 color;
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelMatrix;

out vec3 vertexColorToFrag;
out vec4 positionToFrag;
out vec3 normalToFrag;

void main()
{  
  vertexColorToFrag = color / 255.0;
  positionToFrag = modelMatrix * vec4(position, 1.0);  
  normalToFrag = normal;
  gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
}