#version 330 core

uniform vec4 color;

in vec2 TexCoord;

uniform sampler2D ourTexture;

out vec4 FragColor;
void main() {
    FragColor = texture(ourTexture, TexCoord) * color;
}