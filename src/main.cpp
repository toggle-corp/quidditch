#include <stdinc.h>
#include <Application.h>

int main() {
    try {
        Application application;
        application.run();
    }
    catch (const Exception& exception) {
        std::cout << exception.what() << std::endl;
    }
    return 0;
}
