#version 330 core

// TODO:
// Implement Flat shading

in vec2 fragTexCoord;
in vec4 fragWorldPos;
in vec3 fragNormal;

uniform sampler2D ourTexture;
uniform vec3 camera;

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
    
    
    vec3 obj_color = vec3(texture(ourTexture, fragTexCoord));

    vec3 ambient = La * Ka; // Ambient color
    

    vec3 N = normalize(fragNormal);
    vec3 L = normalize(lightPos - fragWorldPos.xyz);

    float diffuseIntensity = max(0.0, dot(L, N));
    vec3 diffuse = Ld * Kd * diffuseIntensity; 

    vec3 V = normalize(camera-fragWorldPos.xyz); 
    vec3 R = reflect(-L, N);
    float spec = pow(max(0.0, dot(V, R)), a);
    vec3 specular = vec3(0.5, 0.5, 0.5) * spec; // Specular color


    FragColor = vec4((ambient + diffuse + specular) * obj_color, 1.0);
}