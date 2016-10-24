#pragma once
#include <graphics/Texture.h>
#include <graphics/Mesh.h>

class Model {
public:
    Model(const std::string& path);

    void render(const glm::mat4& model, const RenderState& renderState) {
        for (unsigned int i=0; i<mMeshes.size(); ++i) {
            mMeshes[i]->render(mMaterials[mMeshMaterials[i]],
                model, renderState);
        }
    }

private:
    std::vector<std::shared_ptr<Mesh>> mMeshes;
    std::vector<std::string> mMeshMaterials;

    std::map<std::string, std::shared_ptr<Material>> mMaterials;
};