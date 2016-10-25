#include <stdinc.h>
#include <Application.h>


Application::Application()
    : mWidth(800), mHeight(600)
{
    if (!glfwInit()) {
        throw Exception("Couldn't initialize GLFW'");
    }

    // Try setting opengl context 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Floating window in i3
    // TODO: remove
    glfwWindowHint(GLFW_RESIZABLE, false);

    // Create the window
    mWindow = glfwCreateWindow(mWidth, mHeight, "Quidditch", 0, 0);
    glfwSetWindowUserPointer(mWindow, this);
    glfwMakeContextCurrent(mWindow);

    // TODO: Check if created opengl context is less than 3.3

    // Enable GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw Exception(std::string("Error ") +
            (const char*)glewGetErrorString(GLEW_VERSION));
    }

    // Callbacks
    glfwSetFramebufferSizeCallback(mWindow,
        [](GLFWwindow* window, int width, int height) {
            Application * app = (Application*)
                glfwGetWindowUserPointer(window);
            app->mWidth = width;
            app->mHeight = height;
            app->resize();
        });
    
}

Application::~Application() {
    cleanUp();
    glfwTerminate();
}

void Application::run(Timer& timer) {
    init();
    glfwGetFramebufferSize(mWindow, &mWidth, &mHeight);
    resize();

    timer.reset();
    while(!glfwWindowShouldClose(mWindow)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        timer.update([this](double dt){
            update(dt);
        });
        render();

        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }
}

void Application::init() {
    glClearColor(0.396f, 0.612f, 0.937f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    mWorld.reset(new PhysicsWorld());

    mCamera.reset(new Camera());
    mModel.reset(new Model("model-converter/bin/homer.out"));
}

void Application::resize() {
    glViewport(0, 0, mWidth, mHeight);
    mCamera->resize(mWidth, mHeight);
}

void Application::update(double dt) {
    mWorld->step(dt);
}

void Application::render() {
    RenderState state;
    state.camera = mCamera->getViewProjection();

    glm::mat4 model = glm::translate(glm::mat4(), glm::vec3(0, 0, -100.0f));
    mModel->render(model, state);
}

void Application::cleanUp() {

}