#ifndef H_MESH
#define H_MESH

class Mesh {
private:
    unsigned int vbo, vao, numIndices;
    unsigned int ebo;
public:
    Mesh(float* vertexData, unsigned int* indices, unsigned int numVertices, unsigned int numTriangles);
    ~Mesh();

    void render() const;
};

#endif