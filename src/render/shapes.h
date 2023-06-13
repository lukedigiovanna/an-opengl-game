#ifndef H_SHAPES
#define H_SHAPES

#include "Shape.h"

static float v_triangle[] = {
    -0.5f, -0.289f,
    0.5f, -0.289f,
    0.0f, 0.578f
};


static float v_square[] = {
    -0.5f, -0.5f,
    0.5f, -0.5f,
    0.5f, 0.5f,
    -0.5f, 0.5f
};

static unsigned int i_square[] = {
    0, 1, 2,
    0, 2, 3
};

Shape* s_triangle; 
Shape* s_square;

void init_shapes() {
    s_triangle = new Shape(v_triangle, 3);
    s_square = new Shape(v_square, i_square, 6);
}

void destroy_shapes() {
    delete s_triangle;
    delete s_square;
}

#endif