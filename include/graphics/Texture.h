#pragma once

class Texture {
public:
    Texture(const std::string& path);
    Texture(unsigned char* image, int width, int height);

    ~Texture() {
        glDeleteTextures(1, &mTextureId);
    }

    int getWidth() const { return mWidth; }
    int getHeight() const { return mHeight; }

    GLuint getId() const { return mTextureId; }

    // Get the default white texture
    static std::shared_ptr<Texture> getWhiteTexture() {
        auto& textureManager = Manager<Texture>::get();
    
        if (textureManager.has("white_texture")) {
            return textureManager.get("white_texture");
        } else {
            // Create a white texture and return it
            std::vector<unsigned char> wh;
            for (int i=0; i<4*4; ++i)
                wh.push_back(0xFF);
            return textureManager.add("white_texture", &wh[0], 1, 1);
        }
    }

private:
    int mWidth, mHeight;
    GLuint mTextureId;

    void createTexture(unsigned char* image);
};