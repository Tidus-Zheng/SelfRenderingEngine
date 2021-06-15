#version 460 
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
// in vec3 vCol;
// in vec3 vPos;
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vUv;

out vec3 pos;
out vec3 normal;
out vec2 uv;

void main() {
    mat4 MVP = proj * view * model;
    pos = vPos;//  (MVP * vec4(vPos.xyz, 1.0)).xyz;
    vec4 mor = model * vec4(vNormal, 1.0);
    normal = (mor / mor.w).xyz;
    uv = vUv;
    gl_Position = MVP * vec4(vPos.xyz, 1.0);
    // color = vCol;
}