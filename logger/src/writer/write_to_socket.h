#pragma once

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include "writer/write_strategy.h"

namespace logger::writer {
/// @brief Provides interface to write to POSIX socket
class WriteToSocket : public WriteStrategy {
private:
    int socket_desc_;

public:
    /// @param port -- connection port (in machine byte order)
    /// @param sin_addr -- connection IP address (can be INADDR_ANY)
    WriteToSocket(unsigned short port, in_addr_t sin_addr);

    ~WriteToSocket() {
        close(socket_desc_);
    }

    virtual void Write(std::string const& msg) override {
        char const* message = msg.c_str();
        send(socket_desc_, message, msg.size(), 0);
    }
};
}  // namespace logger::writer
