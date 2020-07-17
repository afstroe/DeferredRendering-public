#version 330 core
#define GLSLIFY 1

in vec3 vertexColorToFrag;
in vec4 positionToFrag;
in vec3 normalToFrag;

layout (location = 0) out vec4 diffuseColor;
layout (location = 1) out vec3 positions;
layout (location = 2) out vec3 normals;

uniform struct ProjectorData{
	vec3 position;
	vec3 direction;
	sampler2D texture;
} projectorData;

void main()
{
  diffuseColor = vec4(vertexColorToFrag, 1.0);
  positions	= vec3(positionToFrag.xyz);
  normals	= vec3(normalToFrag.xyz);

	vec3 pv = normalize(positionToFrag.xyz - projectorData.position);	
	float dist = length(positionToFrag.xyz - projectorData.position);	
	vec3 d = normalize(projectorData.direction);

	if((dot(pv, d)) > abs(cos(10 * 0.0174533)))
	{
		vec2 st = vec2(0.5, 100 * dot(pv, d));
		
		diffuseColor = texture2D(projectorData.texture, st);
    
    if(length(diffuseColor) < 0.2)
    {
      normals = vec3(-1, -1, -1);
    }
    else
    {
      normals = vec3(1, 1, 1);      
    }
    
	}
}