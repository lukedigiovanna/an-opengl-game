#ifndef H_CHUNK
#define H_CHUNK

#include "../render/Shader.h"

#include "voxels.h"

#define CHUNK_SIZE 8

/**
 * A chunk is a 64x64x64 segment of the world
 * This class does not contain positional 
 */
class Chunk {
private:
    unsigned char grid[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
public:
    Chunk();

    /**
     * @brief Fills in the voxel information using an algorithm
     *  based on the given seed and chunk position. Chunk (0, 0) is 
     *  the center of the world and is where the player will spawn
     * 
     * @param seed A number to base the deterministical world generation algorithm on.
     * @param cx The x chunk coordinate of the chunk.
     * @param cz The z chunk coordinate of the chunk.
     */
    void generate(unsigned int seed, int cx, int cz);

    // void load(/* from a file*/);

    // Renders this chunk 
    void render(const Shader& shader, int cx, int cz) const;
};

#endif
