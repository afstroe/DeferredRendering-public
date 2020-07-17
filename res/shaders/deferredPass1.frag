#version 330 core

uniform sampler2D _diffuse; 
uniform sampler2D _position;
uniform sampler2D _normals;


uniform vec3 cameraPosition;
uniform vec3 lightPosition;

const int numLights = 3;
uniform vec3 lights[numLights];
uniform vec3 lightColors[numLights];


layout (location = 0) out vec4 color;

in vec2 texCoords0ToFrag;

uniform struct ProjectorData{
	vec3 position;
	vec3 direction;
	sampler2D texture;
} projectorData;


vec4 computeLightColor(int i, vec4 diffuseColor, vec4 position, vec3 normal)
{
	vec3 lightColor = lightColors[i];

	// normalize the incoming n, l anf v vectors
	vec3 n = normalize(normal);
	vec3 l = normalize(lights[i]);
	vec3 v = normalize(lights[i] - position.xyz);
	
	// the reflection of the light source into the rendered surface
	vec3 r = reflect(normalize(lights[i] - cameraPosition), n);
	
	// the diffuse and specular components for each fragment
	vec3 ambient = lightColor * 0.1;
	vec3 diffuse = diffuseColor.rgb * max(dot(n, l), 0.0);
	vec3 specular = pow(max(dot(r, v), 0.0), 10) * lightColor;
	

	return vec4((ambient * diffuse + specular), 1.0);
}

void main()
{
  vec4 diffuseColor = texture2D(_diffuse, texCoords0ToFrag.st);
  vec4 position = texture2D(_position, texCoords0ToFrag.st);
  vec3 normal = texture2D(_normals, texCoords0ToFrag.st).xyz;
	vec3 lightColor = vec3(1, 1, 1);

	color = vec4(0);

	for(int i = 0; i < 3; ++i)
	{
		color += computeLightColor(i, diffuseColor, position, normal);
	}

	vec3 pv = normalize(position.xyz - projectorData.position);
	
	float dist = length(position.xyz - projectorData.position);
	
	vec3 d = normalize(projectorData.direction);

	if((dot(pv, d)) > abs(cos(10 * 0.0174533)))
	{
		// vec2 st = vec2(0.5, 10 * dot(pv, d));
		
		// color = vec4(1.0, 0.0, 0.0, 1.0) + texture2D(projectorData.texture, st);
		color = mix(color, vec4(1), 0.3);
	}
}
