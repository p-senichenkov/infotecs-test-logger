#include "writer_tests.h"

#include <thread>

#include "writer/write_to_stream.h"
#include "writer/writer.h"

namespace test::writer {
using namespace logger;
using namespace logger::writer;

bool NormalData() {
    std::ostringstream oss;
    Writer writer{std::make_unique<WriteToStream>(oss)};

    std::thread writing_thread{&Writer::Run, &writer};

    writer.Write("a");
    writer.Write("b");
    writer.Write("c");

    writer.Stop();

    writing_thread.join();
    return oss.str() == "abc";
}

bool EmptyMessages() {
    std::ostringstream oss;
    Writer writer{std::make_unique<WriteToStream>(oss)};

    std::thread writing_thread{&Writer::Run, &writer};

    writer.Write("");
    writer.Write("");

    writer.Stop();

    writing_thread.join();
    return oss.str().empty();
}
}  // namespace test::writer
