#pragma once
#include <GLFW/glfw3.h>
#include <utils/Timer.h>
#include <graphics/Camera.h>
#include <graphics/Model.h>

class Application {
public:
    Application();
    ~Application();

    void run(Timer& timer);

private:
    GLFWwindow* mWindow;

    int mWidth, mHeight;

    void init();
    void update(double dt);
    void render();
    void resize();
    void cleanUp();

    // We can only construct resources, once everything like OpenGL context is
    // properly initialized. So we store pointers for late construction.

    std::shared_ptr<Camera> mCamera;
    std::shared_ptr<Model> mModel; 
};