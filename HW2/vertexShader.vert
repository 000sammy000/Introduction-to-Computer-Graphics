#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

uniform float squeezeFactor;
uniform float offest;
uniform float time;
uniform bool tremble;

out vec2 texCoord;
out vec3 normal;

vec4 worldPos;

float random(vec2 uv, float seed) {
    return fract(sin(dot(uv, vec2(12.9898, 78.233)) + seed) * 43758.5453);
}

void main()
{
	// TODO: Implement squeeze effect and update normal transformation
	//   1. Adjust the vertex position to create a squeeze effect based on squeezeFactor.
	//   2. Update worldPos using the model matrix (M).
	//   3. Calculate the final gl_Position using the perspective (P), view (V), and updated worldPos.
	//   4. Update the normal transformation for lighting calculations.
	// Note: Ensure to handle the squeeze effect for both y and z coordinates.
	
	vec3 squeezedPos = aPos;
    squeezedPos.y += aPos.z * sin(squeezeFactor) / 2.0;
    squeezedPos.z += aPos.y * sin(squeezeFactor) / 2.0;

	worldPos = M * vec4(squeezedPos, 1.0);

	gl_Position = P * V * worldPos;
	
	if(tremble){
		float amplitude = 1;
		float frequency = 10.0;
		float randValue = random(squeezedPos.xz, time);
		vec3 deform = squeezedPos + amplitude * sin(frequency * time) * normalize(aNormal) * (randValue * 2.0 - 1.0);

		vec4 finalPosition = M * vec4(deform, 1.0);
		gl_Position = P * V * finalPosition ;
	
	}
	
	mat3 normalMatrix = transpose(inverse(mat3(M)));
    normal = normalize(normalMatrix * aNormal);

	


	texCoord = aTexCoord;

}