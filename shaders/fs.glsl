#version 330 core

struct Light {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 lightColor;
uniform float ambientStrength;
uniform vec3 lightPosition;

uniform vec3 objectColor;

uniform vec3 viewPosition;

in vec3 Normal;
in vec2 TexCoord;

in vec3 FragPos;

uniform sampler2D ourTexture;

out vec4 FragColor;
void main() {
    vec3 ambient = ambientStrength * lightColor;

    vec4 texColor = texture(ourTexture, TexCoord);

    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(lightPosition - FragPos);

    float diff = max(dot(norm, lightDirection), 0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5;

    vec3 viewDirection = normalize(viewPosition - FragPos);
    vec3 reflectDirection = reflect(-lightDirection, norm);

    float spec = pow(max(dot(viewDirection, reflectDirection), 0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec4 result = texColor * vec4(objectColor * (ambient + diffuse + specular), 1.0);

    FragColor = result;
}