#version 460
in vec3 pos;
in vec3 normal;
in vec2 uv;
in vec3 tangent;
in vec3 bitangent;

layout(binding = 0) uniform sampler2D texture_diffuse;
layout(binding = 1) uniform sampler2D texture_normal;
layout(binding = 2) uniform sampler2D texture_specular;

uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 cameraPos;

void main() {
    // gl_FragColor = texture(texture_d1, uv);
    // vec3 n = texture(texture_normal, uv).xyz;
    vec3 n = normal;
    vec3 L = lightDir;
    vec3 E = normalize(cameraPos);
    vec3 halfEye = (L + E) / 2;
    vec3 R = normalize(-reflect(L, n));

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    vec3 diffuse = max(dot(n, L), 0.0) * lightColor;
    vec3 specular = pow(max(dot(E, R), 0.0), 8) * lightColor;
    // vec3 specular = texture(texture_specular, uv).xyz * lightColor;
    vec3 phong = (ambient + diffuse + specular) * texture(texture_diffuse, uv).xyz;
    gl_FragColor = vec4(phong,1);
    // gl_FragColor = vec4(specular, 1);
    // gl_FragColor = texture(texture_specular, uv);
}
