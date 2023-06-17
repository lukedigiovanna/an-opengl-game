// Stores a collection of all textures, operates similarly to meshes.h
#ifndef H_TEXTURES
#define H_TEXTURES

#include "Texture.h";

extern Texture* BLANK;
extern Texture* DIRT_BLOCK;

void init_textures();
void destroy_textures();

#endif