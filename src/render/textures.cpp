#include "textures.h"
#include "../stb_image.h"

using namespace textures;

Texture* textures::BLANK;
Texture* textures::DIRT_BLOCK;
Texture* textures::DIAMOND_ORE_BLOCK;
Texture* textures::EMERALD_BLOCK;
Texture* textures::ROSE;

void textures::init() {
    stbi_set_flip_vertically_on_load(true);
    BLANK = new Texture("resources/blank.png");
    DIRT_BLOCK = new Texture("resources/dirt.png");
    DIAMOND_ORE_BLOCK = new Texture("resources/diamond.png");
    EMERALD_BLOCK = new Texture("resources/emerald.png");
    ROSE = new Texture("resources/rose.png");
}

void textures::destroy() {
    delete BLANK;
    delete DIRT_BLOCK;
    delete DIAMOND_ORE_BLOCK;
    delete EMERALD_BLOCK;
    delete ROSE;
}