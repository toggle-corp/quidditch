#pragma once

class Camera {
public:
    Camera() {
        // position, target, up
        mView = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    void resize(int width, int height) {
        mProjection = glm::perspective(120.0f, (float)width/(float)height,
            0.001f, 100000.0f);
    }

    glm::mat4 getViewProjection() const {
        return mProjection * mView;
    }

private:
    glm::mat4 mProjection, mView;
};