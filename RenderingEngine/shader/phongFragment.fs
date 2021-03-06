#version 460
in vec3 pos;
in vec3 normal;
in vec2 uv;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_normal;
uniform sampler2D texture_specular;

uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 cameraPos;

void main() {
    // gl_FragColor = texture(texture_d1, uv);
    vec3 n = texture(texture_normal, uv).xyz;
    vec3 L = lightDir;
    vec3 E = normalize(-pos);
    vec3 R = normalize(-reflect(L, n));

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    vec3 diffuse = max(dot(normal, L), 0.0) * lightColor;
    vec3 specular = pow(max(dot(E, R), 0.0), 32) * lightColor;
    // vec3 specular = texture(texture_specular, uv).xyz * lightColor;

    vec3 phong = (ambient + diffuse + specular) * texture(texture_diffuse, uv).xyz;
    gl_FragColor = vec4(phong, 1.0);
}