#include <iostream>

#include "logger_tests.h"
#include "socket_tests.h"
#include "test.h"
#include "writer_tests.h"

using namespace test;

unsigned RunTests(std::vector<Test> const& tests) {
    unsigned failed_tests = 0;

    for (Test const& test : tests) {
        std::cout << test.name << ": RUN...\n";
        auto result = test.body();
        std::cout << '\t' << (result ? "SUCCESS" : "FAIL") << '\n';
        if (!result) {
            ++failed_tests;
        }
    }

    return failed_tests;
}

int main() {
    unsigned failed_tests = 0;

    std::cout << "* Writer tests *\n";
    failed_tests += RunTests(writer_tests);

    std::cout << "* Logger tests *\n";
    failed_tests += RunTests(logger_tests);

    std::cout << "* Socket tests *\n";
    failed_tests += RunTests(socket_tests);

    if (failed_tests) {
        std::cout << failed_tests << " tests failed\n";
    } else {
        std::cout << "All tests passed\n";
    }
}
