#ifndef H_VOXELS
#define H_VOXELS

#include "../render/Texture.h"
#include "../render/textures.h"

struct Voxel {
    Texture* texture;
};

/*
* Header only file.
* Statically defines the mapping from unsigned characters to
* their respective Voxel 
*/

#define MAX_NUM_VOXELS 256
namespace voxels {
extern Voxel map[MAX_NUM_VOXELS];
}

#endif