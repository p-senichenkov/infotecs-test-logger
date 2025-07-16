#pragma once

#include <functional>
#include <string>

namespace test {
struct Test {
    std::string name;
    std::function<bool(void)> body;
};
}  // namespace test
