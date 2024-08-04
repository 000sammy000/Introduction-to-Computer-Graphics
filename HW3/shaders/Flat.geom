#version 330 core

// TODO:
// Implement Flat shading

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;


in VS_OUT {
	vec2 texCoord;
    vec4 worldPos;
    vec3 normal;

} gs_in[];

out vec2 fragTexCoord;
out vec4 fragWorldPos;
out vec3 fragNormal;

void main(void)
{
	vec3 edge1 = gs_in[1].worldPos.xyz -gs_in[0].worldPos.xyz;
    vec3 edge2 = gs_in[2].worldPos.xyz - gs_in[0].worldPos.xyz;
    vec3 normal = normalize(cross(edge1, edge2));
    
    for(int i = 0; i < 3; ++i)
    {
        fragTexCoord = gs_in[i].texCoord;
        fragWorldPos = gs_in[i].worldPos;
        fragNormal =  normal;
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();

}