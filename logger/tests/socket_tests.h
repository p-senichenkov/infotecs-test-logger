#pragma once

#include <netinet/in.h>
#include <string>
#include <unistd.h>

#include "test.h"

namespace test {
namespace sockets {
/// Utility RAII-wrapper for server-side socket
class ServerSocket {
private:
    int socket_fd_;
    int client_socket_;

public:
    ServerSocket(unsigned short port, in_addr_t addr);

    ~ServerSocket() {
        close(socket_fd_);
    }

    void Accept() {
        client_socket_ = accept(socket_fd_, nullptr, nullptr);
    }

    std::string Recieve();
};

bool SocketLogger();
}  // namespace sockets

static std::vector<Test> const socket_tests{{"Socket logger", sockets::SocketLogger}};
}  // namespace test
