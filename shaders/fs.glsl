#version 330 core

struct Light {
    vec4 vector; // either position or direction, if direction set w to 0
    vec3 color;

    float ambient;
    float diffuse;
    float specular;
};

uniform int numLights;

#define MAX_NUM_LIGHTS 8
uniform Light lights[MAX_NUM_LIGHTS];

uniform vec3 viewPosition;

in vec3 Normal;
in vec2 TexCoord;

in vec3 FragPos;

uniform sampler2D ourTexture;

uniform vec3 objectColor;

out vec4 FragColor;
void main() {
    vec4 texColor = texture(ourTexture, TexCoord);

    if (texColor.a < 0.1) 
        discard;
    
    vec3 norm = normalize(Normal);

    vec3 result = vec3(0.0);

    for (int i = 0; i < numLights; i++) {
        Light light = lights[i];

        // ambient
        vec3 ambient = light.ambient * light.color;

        float attenuation = 1.0;

        // diffuse
        vec3 lightDirection;
        if (light.vector.w == 0.0) { // we are direction light
            lightDirection = -normalize(vec3(light.vector));
        }
        else { // we are point light
            vec3 diffVec = vec3(light.vector) - FragPos;
            lightDirection = normalize(diffVec);
            float d = length(diffVec);
            attenuation = 1.0 / (1.0 + 0.09 * d + 0.032 * d * d);
        }
        float diff = max(dot(norm, lightDirection), 0);
        vec3 diffuse = diff * light.diffuse * light.color;

        // sepcular
        vec3 viewDirection = normalize(viewPosition - FragPos);
        vec3 reflectDirection = reflect(-lightDirection, norm);
        float spec = pow(max(dot(viewDirection, reflectDirection), 0), 16);
        vec3 specular =  spec * light.specular * light.color;

        // combine all parts together
        vec3 thisLight = attenuation * (ambient + diffuse + specular);
        
        result += thisLight;
    }

    FragColor = texColor * vec4(objectColor * result, 1.0);
}