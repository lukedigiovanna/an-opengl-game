#include "meshes.h"

static float v_square[] = {
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
};

static unsigned int i_square[] = {
    0, 1, 2,
    0, 2, 3
};

static float v_circle[] = {
    0.0000f, 0.0000f, 0.0000f, 0.5000f, 0.5000f, 0.5000f, 0.0000f, 0.0000f, 1.0000f, 0.5000f, 0.4755f, 0.1545f, 0.0000f, 0.9755f, 0.6545f, 0.4045f, 0.2939f, 0.0000f, 0.9045f, 0.7939f, 0.2939f, 0.4045f, 0.0000f, 0.7939f, 0.9045f, 0.1545f, 0.4755f, 0.0000f, 0.6545f, 0.9755f, 0.0000f, 0.5000f, 0.0000f, 0.5000f, 1.0000f, -0.1545f, 0.4755f, 0.0000f, 0.3455f, 0.9755f, -0.2939f, 0.4045f, 0.0000f, 0.2061f, 0.9045f, -0.4045f, 0.2939f, 0.0000f, 0.0955f, 0.7939f, -0.4755f, 0.1545f, 0.0000f, 0.0245f, 0.6545f, -0.5000f, 0.0000f, 0.0000f, 0.0000f, 0.5000f, -0.4755f, -0.1545f, 0.0000f, 0.0245f, 0.3455f, -0.4045f, -0.2939f, 0.0000f, 0.0955f, 0.2061f, -0.2939f, -0.4045f, 0.0000f, 0.2061f, 0.0955f, -0.1545f, -0.4755f, 0.0000f, 0.3455f, 0.0245f, -0.0000f, -0.5000f, 0.0000f, 0.5000f, 0.0000f, 0.1545f, -0.4755f, 0.0000f, 0.6545f, 0.0245f, 0.2939f, -0.4045f, 0.0000f, 0.7939f, 0.0955f, 0.4045f, -0.2939f, 0.0000f, 0.9045f, 0.2061f, 0.4755f, -0.1545f, 0.0000f, 0.9755f, 0.3455f
};

static unsigned int i_circle[] = {
    0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 5, 0, 5, 6, 0, 6, 7, 0, 7, 8, 0, 8, 9, 0, 9, 10, 0, 10, 11, 0, 11, 12, 0, 12, 13, 0, 13, 14, 0, 14, 15, 0, 15, 16, 0, 16, 17, 0, 17, 18, 0, 18, 19, 0, 19, 20, 0, 20, 21, 0, 19, 1
};

static float v_cube[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom left
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom right
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top right
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top left
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom left
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // bottom right
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, // top right
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, // top left
};

static unsigned int i_cube[] = {
    0, 1, 2, // front face
    0, 2, 3,
    4, 5, 6,
    4, 6, 7,
    1, 2, 6,
    1, 6, 5,
    2, 3, 6,
    3, 6, 7,
    0, 3, 7,
    0, 7, 4,
    0, 1, 5,
    0, 5, 4
};

Mesh* m_cube; 
Mesh* m_square; 
Mesh* m_circle;

void init_meshes() {
    m_square = new Mesh(v_square, i_square, 4, 2);
    m_circle = new Mesh(v_circle, i_circle, 21, 21);
    m_cube = new Mesh(v_cube, i_cube, 8, 12);
}

void destroy_meshes() {
    delete m_square;
    delete m_circle;
    delete m_cube;
}