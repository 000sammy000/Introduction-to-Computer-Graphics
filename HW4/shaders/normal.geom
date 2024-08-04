#version 330 core

layout (triangles) in;
layout (line_strip, max_vertices = 6) out;
//Input/Output part is important, so be sure to check how everything works

in VS_OUT {
	vec3 normal;
	vec3 fragpos;
	vec2 texCoord;
} gs_in[];

uniform mat4 P;
uniform vec3 windshift;
uniform vec3 jumpDirection;
uniform float freeze_length;

out vec3 fragposGS;
out vec3 normalGS;
out vec2 texCoordGS;

//out vec3 color;


//This is the most important part we want you to implement on yourself
//Use demo code for a learning example and design a geometry shader for your object

float rand(vec2 co){
    float random=fract(sin(dot(co.xy, vec2(12.9898,78.233))) * 43758.5453);
	if (random<0.8) {
		random=0;
	}
	return random;
}

void main()
{	
	for (int i = 0; i < gl_in.length(); ++i) {

	    fragposGS = gs_in[i].fragpos;
        normalGS = normalize(gs_in[i].normal);
		texCoordGS = gs_in[i].texCoord;

        if(freeze_length>0){
			gl_Position = P * gl_in[i].gl_Position;
			EmitVertex();
			gl_Position = P * gl_in[i].gl_Position + vec4(gs_in[i].normal , 0.0)*freeze_length;
			EmitVertex();
		
		}

		gl_Position = P * gl_in[i].gl_Position;
        EmitVertex();
		gl_Position = P * gl_in[i].gl_Position - vec4(jumpDirection, 0.0) * 5*rand(gl_in[i].gl_Position.xy);
        EmitVertex();
	}
	EndPrimitive();
  
}