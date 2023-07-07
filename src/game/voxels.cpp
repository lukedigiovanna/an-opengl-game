#include "voxels.h"

namespace voxels {
Voxel map[MAX_NUM_VOXELS] = {
    { .texture=nullptr },  // 0 is AIR (nothing)
    { .texture=&textures::DIRT_BLOCK },
    { .texture=&textures::EMERALD_BLOCK }
};
}