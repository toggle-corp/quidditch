#pragma once
#include <graphics/Material.h>
#include <graphics/Texture.h>

class DiffuseMaterial : public Material {
public:
    DiffuseMaterial(const glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                    std::shared_ptr<Texture> texture
                        = Texture::getWhiteTexture())
        : color(color), texture(texture) 
    {
        mProgram.reset(new Program(
            Shader::get("shaders/vs_diffuse.glsl", GL_VERTEX_SHADER),
            Shader::get("shaders/fs_diffuse.glsl", GL_FRAGMENT_SHADER)
        ));
    }

    glm::vec4 color;
    std::shared_ptr<Texture> texture;

    void setUniforms() {
        mProgram->setUniform("diffuseColor", color);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->getId());
        mProgram->setUniform("diffuseTexture", 0);
    }
};