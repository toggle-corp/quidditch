#pragma once
#include <graphics/Program.h>

class Material {
public:
    void use() {
        mProgram->use();
        setUniforms();
    }
    
    virtual void setUniforms() = 0;

    std::shared_ptr<Program> getProgram() { return mProgram; }

protected:
    std::shared_ptr<Program> mProgram;
};