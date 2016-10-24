#include <stdinc.h>
#include <graphics/Model.h>


Model::Model(const std::string& path) {
    // TODO: Exceptions

    std::string folder = getFolder(path);
    std::ifstream file(path, std::ios::in | std::ios::binary);

    // The global resource managers
    Manager<Texture> textureManager;

    // Load materials
    unsigned int numMaterials;
    file.read((char*)&numMaterials, sizeof(numMaterials));
    for (unsigned int i=0; i<numMaterials; ++i) {
        std::string key = readString(file);

        // Diffuse color
        glm::vec4 color;
        file.read((char*)&color[0], sizeof(glm::vec4));

        // Diffuse texture
        // Assuming texture is in "<model_folder>/textures/"
        std::string texturePath = folder + "/textures/" + readString(file);
        
        // Make sure to reuse texture for same path
        std::shared_ptr<Texture> texture;
        if (textureManager.has(texturePath)) 
            texture = textureManager.get(texturePath);
        else
            texture = textureManager.add(texturePath, texturePath);

        // Create the diffuse material
        mMaterials[key] = std::shared_ptr<Material>(
            new DiffuseMaterial(color, texture));
    }

    // Load meshes
    unsigned int numMeshes;
    file.read((char*)&numMeshes, sizeof(numMeshes));
    for (unsigned int i=0; i<numMeshes; ++i) {
        unsigned int  num;

        // Vertices
        file.read((char*)&num, sizeof(num));
        std::vector<Vertex> vertices(num);
        file.read((char*)&vertices[0], num*sizeof(Vertex));

        // Indices
        file.read((char*)&num, sizeof(num));
        std::vector<GLuint> indices(num);
        file.read((char*)&indices[0], num*sizeof(GLuint));

        // Material
        std::string materialKey = readString(file);

        // Create the mesh
        mMeshes.push_back(std::shared_ptr<Mesh>(new Mesh(vertices, indices)));
        mMeshMaterials.push_back(materialKey);
    }
}