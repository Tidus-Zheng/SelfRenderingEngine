#version 460
in vec3 pos;
in vec3 normal;
in vec2 uv;

uniform sampler2D texture_d1;
uniform sampler2D texture_d2;
uniform sampler2D texture_d3;
uniform sampler2D texture_s1;
uniform sampler2D texture_s2;

uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 cameraPos;

void main() {
    // gl_FragColor = texture(texture_d1, uv);
    vec3 L = lightDir;
    vec3 E = normalize(-pos);
    vec3 R = normalize(-reflect(L, normal));

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    vec3 diffuse = max(dot(normal, L), 0.0) * lightColor;
    vec3 specular = pow(max(dot(E, R), 0.0), 32) * lightColor;

    vec3 phong = (ambient + diffuse + specular) * texture(texture_d1, uv).xyz;
    gl_FragColor = vec4(phong, 1.0);
}