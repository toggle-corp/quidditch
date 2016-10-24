#pragma once
#include <GLFW/glfw3.h>

class Application {
public:
    Application();
    ~Application();

    void run();

private:
    GLFWwindow* mWindow;

    int mWidth, mHeight;

    void init();
    void update(double dt);
    void render();
    void resize();
    void cleanUp();
};