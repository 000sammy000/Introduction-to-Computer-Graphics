#version 330 core

// TODO:
// Implement Toon shading
in vec2 texCoord;
in vec4 worldPos;
in vec3 normal;

uniform sampler2D ourTexture;



out vec4 FragColor;

void main()
{
	vec3 obj_color = vec3(texture(ourTexture, texCoord));
	vec4 color;
	vec3 lightPos = vec3(10, 10, 10);
	vec3 N = normalize(normal);
	vec3 L = (normalize(vec4(lightPos, 1.0) - worldPos)).xyz;
	float intensity = max(dot(L, N), 0.0);
	
	
	if(intensity > 0.95) color = vec4(1.0, 0.8, 0.8, 1.0);
	else if(intensity > 0.5) color = vec4(0.45, 0.3, 0.3, 1.0);
	else if(intensity > 0.25) color = vec4(0.3, 0.2, 0.2, 1.0);
	else color = vec4(0.15, 0.1, 0.1, 1.0);

	FragColor = color;

}