#version 330 core

layout (location = 0) in vec2 aPos;

uniform vec2 position;
uniform vec2 dimension;

uniform vec2 screenDimension;

uniform float rotation;

void main() {
    mat2 rotationMatrix = mat2(
        cos(rotation), -sin(rotation),
        sin(rotation), cos(rotation)
    );

    vec2 sPos = (rotationMatrix * aPos.xy * dimension.xy + position) / (screenDimension.xy / 2);
    gl_Position = vec4(sPos.x, sPos.y, 0, 1.0);
}