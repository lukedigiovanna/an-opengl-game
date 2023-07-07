#include "Chunk.h"

#include <glm/gtc/matrix_transform.hpp>
#include "../render/meshes.h"

#include <iostream>

Chunk::Chunk() {
    // by default the entire chunk is air.
}

void Chunk::generate(unsigned int seed, int cx, int cz) {
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int z = 0; z < CHUNK_SIZE; z++) {
            this->grid[x][0][z] = 2;
        }
    }
}

void Chunk::render(const Shader& shader, int cx, int cz) const {
    // Basic approach: iterate over the entire chunk and render.
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                float wx = cx * CHUNK_SIZE + x;
                float wy = y;
                float wz = cz * CHUNK_SIZE + z;

                // Set the model matrix in the shader for these coordinates
                glm::mat4 model(1.0f);
                model = glm::translate(model, glm::vec3(wx, wy, wz));
                shader.setMatrix4("model", model);
                // Set the texture of this voxel.
                Voxel voxel = voxels::map[this->grid[x][y][z]];
                // std::cout << voxel.texture << std::endl;
                if (voxel.texture != nullptr) {
                    voxel.texture->bind();
                    // Draw the voxel
                    meshes::CUBE->render();
                }
            }
        }
    }
    // A more scalable approach is described as follows:
    // Maintain a data structure containing the positions that
    // fall along a boundary of air. Only render these voxels.
    // Then when there is any update within this chunk (change of a block
    // to air or vice versa we can update that boundary).
}