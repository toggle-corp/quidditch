#include <stdinc.h>
#include <Model.h>


Model::Model(const std::string& path)
    : mPath(path)
{
    // Import the model from the path to a scene
    Assimp::Importer importer;
    mScene = importer.ReadFile(path,
        aiProcess_Triangulate |
        aiProcess_GenSmoothNormals |
        aiProcess_FlipUVs |
        aiProcess_JoinIdenticalVertices);

    if (!mScene) {
        throw std::runtime_error(
            "Error: Couldn't load scene from file: " + path
        );
    }

    // Load all materials from the scene
    for (unsigned int i=0; i<mScene->mNumMaterials; ++i) {
        loadMaterial("mat"+std::to_string(i), mScene->mMaterials[i]);
    }

    // Load all meshes from the scene
    for (unsigned int i=0; i<mScene->mNumMeshes; ++i) {
        loadMesh(mScene->mMeshes[i]);
    }

    // Load the root node
    loadNode(mScene->mRootNode);
}


void Model::loadNode(aiNode* node)
{
    // Load the children nodes
    for (unsigned int i=0; i<node->mNumChildren; ++i) {
        loadNode(node->mChildren[i]);
    }
}


void Model::loadMaterial(const std::string& name, aiMaterial* material)
{
    Material m;

    // Get diffuse color
    aiColor3D color(0.f, 0.f, 0.f);
    material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
    m.color = glm::vec4(color.r, color.g, color.b, 1.0f);

    // Get texture path
    if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
        aiString str;
        material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
        m.texture = getFilename(str.C_Str());
    }
    else {
        m.texture = "";
    }

    mMaterials[name] = m;
}


void Model::loadMesh(aiMesh* mesh)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // Load the vertices
    vertices.resize(mesh->mNumVertices);
    for (unsigned int i=0; i<mesh->mNumVertices; ++i) {
        Vertex& vertex = vertices[i];
        auto aiVertex = mesh->mVertices[i];
        auto aiNormal = mesh->mNormals[i];

        vertex.position = glm::vec3(
            aiVertex.x, aiVertex.y, aiVertex.z);
        vertex.normal = glm::vec3(
            aiNormal.x, aiNormal.y, aiNormal.z);

        if (mesh->mTextureCoords[0]) {
            vertex.texCoords = glm::vec2(
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y
            );
        }
        else {
            vertex.texCoords = glm::vec2(0,0);
        }
    }

    // Load the indices
    for (unsigned int i=0; i<mesh->mNumFaces; ++i) {
        auto face = mesh->mFaces[i];
        for (unsigned int j=0; j<face.mNumIndices; ++j)
            indices.push_back(face.mIndices[j]);
    }


    Mesh m(vertices, indices);
    // Set material
    m.material = "mat" + std::to_string(mesh->mMaterialIndex);

    mMeshes.push_back(m);
}


void Model::save(const std::string& path)
{
    std::ofstream file(path, std::ios::out | std::ios::binary);
    unsigned int num;

    // Save the materials
    num = mMaterials.size();
    file.write((char*)&num, sizeof(num));
    for (auto const& material: mMaterials) {
        writeString(file, material.first);
        file.write((char*)&material.second.color[0],
            sizeof(glm::vec4));
        writeString(file, material.second.texture);

        // Also try and copy the texture
        copyTexture(path, material.second.texture);
    }

    // Save the meshes
    num = mMeshes.size();
    file.write((char*)&num, sizeof(num));
    for (Mesh& mesh: mMeshes) {
        auto vs = mesh.getVertices();
        auto is = mesh.getIndices();

        // Vertices
        num = vs.size();
        file.write((char*)&num, sizeof(num));
        file.write((char*)&vs[0], vs.size()*sizeof(Vertex));

        // Indices
        num = is.size();
        file.write((char*)&num, sizeof(num));
        file.write((char*)&is[0], is.size()*sizeof(unsigned int));

        // Material
        writeString(file, mesh.material);
    }

    // TODO: Save nodes
}


void Model::copyTexture(const std::string& dest,
    const std::string& filename)
{
    std::string destFolder = getFolder(dest);
    int status = createDirectory(destFolder+"/textures/");

    // TODO: Check status

    // Check if file exists
    std::string folder = getFolder(mPath);
    if (!doesFileExist(folder + "/" + filename))
        std::cout << "Couldn't find texture " << filename << std::endl;

    copyFile(folder+"/"+filename, destFolder+"/textures/"+filename);
}
