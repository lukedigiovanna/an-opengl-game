#ifndef H_MESHES
#define H_MESHES

#include "Mesh.h"

namespace meshes {
extern Mesh* CUBE; 
extern Mesh* SQUARE; 
extern Mesh* CIRCLE; 

void init();

void destroy();
}

#endif