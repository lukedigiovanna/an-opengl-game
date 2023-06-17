// Stores a collection of all textures, operates similarly to meshes.h
#ifndef H_TEXTURES
#define H_TEXTURES

#include "Texture.h"

namespace textures {
extern Texture* BLANK;
extern Texture* DIRT_BLOCK;
extern Texture* DIAMOND_ORE_BLOCK;
extern Texture* EMERALD_BLOCK;
extern Texture* ROSE;

void init();
void destroy();
}

#endif