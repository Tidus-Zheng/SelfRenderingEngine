#version 460
in vec3 color; 
in vec3 pos;

uniform sampler2D texture_d1;
uniform sampler2D texture_d2;
uniform sampler2D texture_d3;
uniform sampler2D texture_s1;
uniform sampler2D texture_s2;

void main() 
{
    // if(pos.x <= 1 &&pos.x >= -1 && pos.y <= 1 && pos.y >= -1)
    //     gl_FragColor = vec4(1, 1, 1, 1.0); 
    // else
        gl_FragColor = vec4(1, 1, 1, 1.0); 
} 