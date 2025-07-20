#pragma once

#include "test.h"

namespace test {
namespace writer {
bool NormalData();

bool EmptyMessages();
}  // namespace writer

static std::vector<Test> writer_tests{{"Normal data", writer::NormalData},
                                      {"Empty messages", writer::EmptyMessages}};
}  // namespace test
