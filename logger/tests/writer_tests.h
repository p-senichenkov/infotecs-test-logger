#pragma once

#include <sstream>
#include <thread>

#include "test.h"
#include "writer/write_to_stream.h"
#include "writer/writer.h"

namespace test {
namespace writer {
bool NormalData();

bool EmptyMessages();
}  // namespace writer

static std::vector<Test> writer_tests{{"Normal data", writer::NormalData},
                                      {"Empty messages", writer::EmptyMessages}};
}  // namespace test
