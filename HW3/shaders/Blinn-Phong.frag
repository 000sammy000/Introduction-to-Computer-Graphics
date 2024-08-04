#version 330 core

// TODO:
// implement Blinn-Phong shading

in vec2 texCoord;
in vec4 worldPos;
in vec3 normal;
in vec3 view_pos;


uniform sampler2D ourTexture;

out vec4 FragColor;

void main()
{
	
	vec3 Ka = vec3(1.0, 1.0, 1.0);
	vec3 Kd = vec3(1.0, 1.0, 1.0);
	vec3 Ks = vec3(0.7, 0.7, 0.7);
	float a = 10.5;
	vec3 La = vec3(0.2, 0.2, 0.2);
	vec3 Ld = vec3(0.8, 0.8, 0.8);
	vec3 Ls = vec3(0.5, 0.5, 0.5);
	vec3 lightPos = vec3(10, 10, 10);
	
	vec3 obj_color = vec3(texture(ourTexture, texCoord));

	vec3 ambient = La * Ka;

	vec3 N = normalize(normal);
	vec3 L = (normalize(lightPos - worldPos.xyz));	
	vec3 diffuse = Ld * Kd  * max(0.0, dot(L, N));
	
	vec3 V = normalize(view_pos - vec3(worldPos));
    vec3 H = normalize(L + V);
	float spec = pow(max(0.0, dot(N,H)), a);
    vec3 specular = Ls * Ks * spec;

	FragColor = vec4((ambient + diffuse + specular)*obj_color, 1.0);

}