#include <stdinc.h>
#include <graphics/Mesh.h>


Mesh::Mesh(const std::vector<Vertex>& vertices,
           const std::vector<GLuint>& indices)
{
    // Generate buffers and arrays
    glGenBuffers(1, &mVBO);
    glGenBuffers(1, &mEBO);
    glGenVertexArrays(1, &mVAO);

    glBindVertexArray(mVAO);

    // Set vertices data to VBO
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
        &vertices[0], GL_STATIC_DRAW);

    // Set indices data to EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
        &indices[0], GL_STATIC_DRAW);

    // Vertex attributes
    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        (GLvoid*)offsetof(Vertex, position));
    // Normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        (GLvoid*)offsetof(Vertex, normal));
    // Texture coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        (GLvoid*)offsetof(Vertex, texCoords));
    // ...


    glBindVertexArray(0);

    mNumElements = indices.size();
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
    glDeleteBuffers(1, &mEBO);
}

void Mesh::render(std::shared_ptr<Material> material, const glm::mat4& model,
                 const RenderState& renderState)
{
    material->use();

    std::shared_ptr<Program> p = material->getProgram();

    if (p->testFlag(USE_STD_3D_UNIFORMS)) {
        p->setUniform("mvpMatrix", renderState.camera*model);
        p->setUniform("modelMatrix", model);
    }

    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLES, mNumElements, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}