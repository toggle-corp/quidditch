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
    void save(const std::string& path);

private:
    void loadNode(aiNode* node);
    void loadMaterial(const std::string& name, aiMaterial* material);
    void loadMesh(aiMesh* mesh);

    const aiScene* mScene;
    std::map<std::string, Material> mMaterials;
    std::vector<Mesh> mMeshes;

    std::string mPath;

    void copyTexture(const std::string& dest, const std::string& filename);
};
