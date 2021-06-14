#version 460 
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
// in vec3 vCol;
// in vec3 vPos;
layout (location = 0) in vec3 vPos;

out vec3 color;
out vec3 pos;


void main() {
    mat4 MVP = proj * view * model;
    pos = (MVP * vec4(vPos.xyz, 1.0)).xyz;
    // gl_Position = MVP * vec4(vPos.xyz, 1.0);
    // color = vCol;
}