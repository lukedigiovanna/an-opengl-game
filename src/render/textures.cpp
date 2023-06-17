#include "textures.h"

using namespace textures;

void textures::init() {
    BLANK = new Texture("resources/blank.png");
    DIRT_BLOCK = new Texture("resources/dirt.png");
}

void textures::destroy() {
    delete BLANK;
    delete DIRT_BLOCK;
}