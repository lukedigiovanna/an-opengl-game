#include "textures.h"
#include "../stb_image.h"

using namespace textures;

namespace textures {
Texture BLANK;
Texture DIRT_BLOCK;
Texture DIAMOND_ORE_BLOCK;
Texture EMERALD_BLOCK;
Texture ROSE;
}

void textures::init() {
    stbi_set_flip_vertically_on_load(true);
    BLANK = Texture("resources/blank.png");
    DIRT_BLOCK = Texture("resources/dirt.png");
    DIAMOND_ORE_BLOCK = Texture("resources/diamond.png");
    EMERALD_BLOCK = Texture("resources/emerald.png");
    ROSE = Texture("resources/rose.png");
}

// void textures::destroy() {
//     delete BLANK;
//     delete DIRT_BLOCK;
//     delete DIAMOND_ORE_BLOCK;
//     delete EMERALD_BLOCK;
//     delete ROSE;
// }