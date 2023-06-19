#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;

out vec3 Normal;
out vec2 TexCoord;

out vec3 FragPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
    vec4 pos = projection * view * model * vec4(inPos, 1.0);

    gl_Position = pos;

    TexCoord = inTexCoord;
    Normal = mat3(transpose(inverse(model))) * inNormal;  
    FragPos = vec3(model * vec4(inPos, 1.0));
}