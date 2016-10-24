#pragma once
#include <graphics/Shader.h>

const int USE_STD_3D_UNIFORMS = 1;

class Program {
public:
    Program(const std::shared_ptr<Shader>& vertexShader,
            const std::shared_ptr<Shader>& fragmentShader,
            int flags = USE_STD_3D_UNIFORMS)
        : mFlags(flags)
    {
        GLuint program = glCreateProgram();
        glAttachShader(program, vertexShader->getId());
        glAttachShader(program, fragmentShader->getId());
        glLinkProgram(program);

        GLint success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            GLchar infoLog[512];
            glGetProgramInfoLog(program, 512, 0, infoLog);

            std::stringstream msg;
            msg << "Linking error: \t" << infoLog << std::endl;

            throw Exception(msg.str());
        }
        mProgramId = program;
    }

    ~Program() {
        glDeleteProgram(mProgramId);
    }

    GLuint getId() const { return mProgramId; }

    void setFlag(int flag) { mFlags |= flag; }
    void unsetFlag(int flag) { mFlags &= ~flag; }
    bool testFlag(int flag) { return mFlags & flag; }
    int getFlags() const { return mFlags; }

    GLint getUniformLocation(const std::string& name) const {
        return glGetUniformLocation(mProgramId, name.c_str());
    }

    // Set uniforms
    void setUniform(const std::string& uniform, bool boolean)
    { glUniform1i(getUniformLocation(uniform), boolean); }
    void setUniform(const std::string& uniform, GLint integer)
    { glUniform1i(getUniformLocation(uniform), integer); }
    void setUniform(const std::string& uniform, GLfloat number)
    { glUniform1f(getUniformLocation(uniform), number); }
    void setUniform(const std::string& uniform, const glm::mat4& matrix)
    { glUniformMatrix4fv(getUniformLocation(uniform), 1, GL_FALSE, glm::value_ptr(matrix)); }
    void setUniform(const std::string& uniform, const glm::vec4& vector)
    { glUniform4fv(getUniformLocation(uniform), 1, glm::value_ptr(vector)); }
    void setUniform(const std::string& uniform, const glm::vec3& vector)
    { glUniform3fv(getUniformLocation(uniform), 1, glm::value_ptr(vector)); }

    // Use this program for next rendering operations
    void use() const {
        glUseProgram(mProgramId);
    }

private:
    GLuint mProgramId;
    int mFlags;
};