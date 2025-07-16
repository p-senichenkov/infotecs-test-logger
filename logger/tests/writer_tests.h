#pragma once

#include <sstream>
#include <thread>

#include "test.h"
#include "writer/write_to_stream.h"
#include "writer/writer.h"

namespace test {
namespace writer {
inline bool NormalData() {
    std::ostringstream oss;
    logger::writer::Writer writer{std::make_unique<logger::writer::WriteToStream>(oss)};

    std::thread writing_thread{&logger::writer::Writer::Run, &writer};

    writer.Write("a");
    writer.Write("b");
    writer.Write("c");

    writer.Stop();

    writing_thread.join();
    return oss.str() == "abc";
}

inline bool EmptyMessages() {
    std::ostringstream oss;
    logger::writer::Writer writer{std::make_unique<logger::writer::WriteToStream>(oss)};

    std::thread writing_thread{&logger::writer::Writer::Run, &writer};

    writer.Write("");
    writer.Write("");

    writer.Stop();

    writing_thread.join();
    return oss.str().empty();
}
}  // namespace writer

static std::vector<Test> writer_tests{{"Normal data", writer::NormalData},
                                      {"Empty messages", writer::EmptyMessages}};
}  // namespace test
