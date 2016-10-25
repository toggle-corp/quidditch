#include <stdinc.h>
#include <Model.h>


int main()
{
    try {
        Model m("models/homer.x");
        m.save("bin/homer.out");

        m.calculateConvexHull();
        m.saveShape("bin/homer.shp");
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
