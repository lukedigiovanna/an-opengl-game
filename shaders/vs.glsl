#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTexCoord;

out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;

void main() {
    TexCoord = inTexCoord;
    
    vec4 pos = projection * view * transform * vec4(inPos, 1.0);

    gl_Position = pos;
}