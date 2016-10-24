#include <stdinc.h>
#include <Application.h>
#include <utils/FixedStepTimer.h>
#include <graphics/materials/DiffuseMaterial.h>

int main() {
    try {
        Application application;
        FixedStepTimer timer(60);
        application.run(timer);
    }
    catch (const Exception& exception) {
        std::cout << exception.what() << std::endl;
    }
    return 0;
}
