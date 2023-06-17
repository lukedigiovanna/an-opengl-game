#ifndef H_TEXTURE
#define H_TEXTURE

#include <string>

class Texture {
private:
    int width, height, nrChannels;
    unsigned char* data;
    unsigned int texture;
public:
    Texture(std::string const& imagePath);
    ~Texture();

    void bind() const;
    void unbind() const;
};

#endif