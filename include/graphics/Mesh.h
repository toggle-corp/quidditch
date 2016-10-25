#pragma once
#include <graphics/materials/DiffuseMaterial.h>
#include <graphics/RenderState.h>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;

    Vertex(const glm::vec3& position,
           const glm::vec3& normal, const glm::vec2& texCoords)
        : position(position), normal(normal), texCoords(texCoords)
    {}

    Vertex(const glm::vec3& position)
        : position(position) {}

    Vertex() {}
};

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices,
         const std::vector<GLuint>& indices);

    virtual ~Mesh();

    void render(std::shared_ptr<Material> material, const glm::mat4& model,
                const RenderState& renderState);

private:
    GLuint mVAO, mVBO, mEBO, mNumElements;
};