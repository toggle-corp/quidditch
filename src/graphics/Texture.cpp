#include <stdinc.h>
#include <graphics/Texture.h>
#include <SOIL/SOIL.h>


Texture::Texture(const std::string& path) {
    // TODO: Exceptions

    unsigned char* image = SOIL_load_image(path.c_str(),
        &mWidth, &mHeight, 0, SOIL_LOAD_RGBA);
    createTexture(image);

    SOIL_free_image_data(image);
}

Texture::Texture(unsigned char* image, int width, int height) {
    mWidth = width;
    mHeight = height;
    createTexture(image);
}

void Texture::createTexture(unsigned char* image) {
    // Create texture object
    glGenTextures(1, &mTextureId);
    glBindTexture(GL_TEXTURE_2D, mTextureId);

    // Set texture data to image
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight,
        0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}