#version 460 
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
// in vec3 vCol;
// in vec3 vPos;
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vUv;
layout(location = 3) in vec3 vTangent;
layout(location = 4) in vec3 vBitangent;

out vec3 pos;
out vec3 normal;
out vec2 uv;
out vec3 tangent;
out vec3 bitangent;

void main() {
    mat4 MVP = proj * view * model;
    pos = vPos;//  (MVP * vec4(vPos.xyz, 1.0)).xyz;
    normal = normalize(mat3(transpose(inverse(model))) * vNormal);
    uv = vUv;
    gl_Position = MVP * vec4(vPos.xyz, 1.0);
    tangent = vTangent;
    bitangent = vBitangent;
    // color = vCol;
}