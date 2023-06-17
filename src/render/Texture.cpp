#include "Texture.h"
#include "../stb_image.h"
#include <glad/glad.h>
#include <iostream>

Texture::Texture(std::string const& imagePath) {
    this->data = stbi_load(imagePath.c_str(), &this->width, &this->height, &this->nrChannels, 0);
    if (!this->data) {
        std::cout << "Failed to load texture" << std::endl;
        return;
    }
    glGenTextures(1, &this->texture);
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(this->data);

    this->unbind();
}

Texture::~Texture() {
    glDeleteTextures(1, &this->texture);
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, this->texture);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}