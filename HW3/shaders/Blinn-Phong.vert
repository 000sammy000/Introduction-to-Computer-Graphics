#version 330 core

// TODO:
// implement Blinn-Phong shading
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform vec3 camera;

out vec2 texCoord;
out vec4 worldPos;
out vec3 normal;
out vec3 view_pos;


void main()
{
	gl_Position = P * V * M * vec4(aPos, 1.0);
	texCoord = aTexCoord;
	worldPos = M * vec4(aPos, 1.0);
	mat4 normal_trans = transpose(inverse(M));
	normal = normalize((normal_trans * vec4(aNormal, 0.0)).xyz);
	view_pos = camera;
    vec3 viewDir = normalize(view_pos);
	
	

}