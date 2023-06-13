#ifndef H_SHAPE
#define H_SHAPE

class Shape {
private:
    unsigned int vbo, vao, numVertices;
    unsigned int ebo;
    bool useEbo = false;
public:
    Shape(float* vertices, unsigned int numVertices);
    Shape(float* vertices, unsigned int* indices, unsigned int numVertices);
    ~Shape();

    void draw() const;
};

#endif