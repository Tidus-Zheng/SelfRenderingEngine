#version 460
in vec3 color; 
in vec3 pos;
void main() 
{
    // if(pos.x <= 1 &&pos.x >= -1 && pos.y <= 1 && pos.y >= -1)
    //     gl_FragColor = vec4(1, 1, 1, 1.0); 
    // else
        gl_FragColor = vec4(color, 1.0); 
} 