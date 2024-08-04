#version 330 core

uniform sampler2D ourTexture;
uniform int update;
uniform float shiningPlace;
uniform int freeze;

in vec3 fragposGS;
in vec3 normalGS;
in vec2 texCoordGS;


//in vec3 color;

out vec4 FragColor;

void main()
{
    vec3 furColor = texture(ourTexture, texCoordGS).xyz;
    
    if(freeze==1){
        FragColor = vec4(1.0,1.0,1.0, 0.3);
    }else if(update==1&&fragposGS.y>shiningPlace&&fragposGS.y<shiningPlace+0.5){
        FragColor = vec4(1.0,1.0,0.0, 0.1);
    }else{
        FragColor = vec4(furColor, 0.3);
    }
    
}