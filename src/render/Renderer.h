#ifndef H_RENDERER
#define H_RENDERER

#include "Shader.h"
#include "color.h"
#include "../utils/Vec2.h"

class Renderer {
private:
    Shader* shader;
    Color fillColor;
    // The width and height of the screen (centered on the position
    Vec2 screenDimension;
    // What coordinate the center of the screen corresponds to
    Vec2 cameraPosition;
public:
    Renderer();
    ~Renderer();

    void setColor(Color color);
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void fillRect(float x, float y, float width, float height);
};

#endif