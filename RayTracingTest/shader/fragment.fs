#version 460
in vec3 pos;
in vec3 normal;
in vec2 uv;

uniform sampler2D texture_d1;
uniform sampler2D texture_d2;
uniform sampler2D texture_d3;
uniform sampler2D texture_s1;
uniform sampler2D texture_s2;

void main() {
    gl_FragColor = texture(texture_d1, uv);
    // gl_FragColor = vec4(pos, 1.0);
}