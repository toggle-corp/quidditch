#pragma once


struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct Texture
{
    std::string filename;
    std::string type;
};


class Mesh
{
public:
    Mesh(const std::vector<Vertex>& vertices,
        const std::vector<unsigned int>& indices)
        : mVertices(vertices), mIndices(indices)
    {}

    std::vector<Vertex>& getVertices() { return mVertices; }
    std::vector<unsigned int>& getIndices() { return mIndices; }
    std::string material;

private:
    std::vector<Vertex> mVertices;
    std::vector<unsigned int> mIndices;
};
