#include <cstdlib>
#include <exception>
#include <iostream>

#include "application.h"

int main() {
    try {
        application::Application app;
        app.Run();
    } catch (std::exception const& e) {
        std::cout << "Error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
}
