#pragma once
#include <Mesh.h>


struct Material
{
    glm::vec4 color;
    std::string texture;
};


class Model
{
public:
    Model(const std::string& path);
    ~Model() {
        if (mShape)
            delete mShape;
    }

    void calculateConvexHull();

    void save(const std::string& path);
    void saveShape(const std::string& path);

private:
    btCollisionShape* mShape;

    void loadNode(aiNode* node);
    void loadMaterial(const std::string& name, aiMaterial* material);
    void loadMesh(aiMesh* mesh);

    const aiScene* mScene;
    std::map<std::string, Material> mMaterials;
    std::vector<Mesh> mMeshes;

    std::string mPath;

    void copyTexture(const std::string& dest, const std::string& filename);
};
