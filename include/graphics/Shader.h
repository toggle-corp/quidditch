#pragma once

class Shader {
public:
    static std::shared_ptr<Shader> get(const std::string& filename,
                             GLenum type)
    {
        // First check if the shader already exists,
        // and if it does, return that shader.
        auto& shaderManager = Manager<Shader>::get();
        if (shaderManager.has(filename)) {
            return shaderManager.get(filename);
        }
        else {
            return shaderManager.add(filename, filename, type);
        }
    }

    Shader(const std::string& filename, GLenum type) {
        std::string str = readFile(filename);
        const char* text = str.c_str();

        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &text, 0);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success) {
            GLchar infoLog[512];
            glGetShaderInfoLog(shader, 512, 0, infoLog);

            std::stringstream msg;
            msg << "Shader compilation error: \t" << filename
                << "\n\n" << infoLog << std::endl;

            throw Exception(msg.str());
        }
        mShaderId = shader;
    }

    virtual ~Shader() {
        glDeleteShader(mShaderId);
    }

    GLuint getId() const { return mShaderId; }

private:
    GLuint mShaderId;
};