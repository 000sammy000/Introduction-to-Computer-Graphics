#version 330 core

// TODO:
// Implement Gouraud shading
in vec2 texCoord;
in vec4 worldPos;

in vec3 normal;
in vec3 ambient;
in vec3 diffuse;
in vec3 specular;

uniform sampler2D ourTexture;

out vec4 FragColor;

void main()
{
	vec3 obj_color = vec3(texture(ourTexture, texCoord));

	FragColor = vec4((ambient+ diffuse + specular)*obj_color, 1.0);

}