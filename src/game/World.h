#ifndef H_WORLD
#define H_WORLD

#include "Chunk.h"

// Defines the chunk width and chunk length
// e.g. 16 = 16 chunks x 16 chunks
#define WORLD_SIZE 16

/**
 * A world contains a 64x64 grid of chunks
 */
class World {
private:
    unsigned int seed;
    // the chunks represents the loaded in memory of the world
    // when a player goes far enough beyond a chunk, that chunk will become deallocated
    // and will need to be reloaded into the game.
    Chunk* chunks[WORLD_SIZE][WORLD_SIZE];
public:
    World(unsigned int seed);

    void generate(int cx, int cz) {
        chunks[cx][cz] = new Chunk();

    }
};

#endif