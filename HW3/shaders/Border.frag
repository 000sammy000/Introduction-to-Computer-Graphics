#version 330 core

// Advanced:
// Implement Border effect

in vec2 texCoord;
in vec4 worldPos;
in vec3 normal;
in vec3 view_pos;

uniform sampler2D ourTexture;

out vec4 FragColor;

void main()
{
	
	
	vec3 obj_color = vec3(texture(ourTexture, texCoord));
	vec3 n_normal = normalize(normal);
	float facing = dot(normalize(view_pos), n_normal);
	vec4 color = vec4(obj_color, 1.0);
	FragColor = mix(color, vec4(1.0, 1.0, 1.0, 1.0), 1.0-facing);
	
	

}