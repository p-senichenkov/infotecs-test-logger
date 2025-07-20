#include "socket_tests.h"

#include <cerrno>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <memory>
#include <netinet/in.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <thread>

#include "log_level.h"
#include "logger.h"
#include "writer/write_to_socket.h"
#include "writer/writer.h"

using namespace logger;
using namespace writer;

namespace test::sockets {
ServerSocket::ServerSocket(unsigned short port, in_addr_t addr) {
    sockaddr_in conn_info;
    conn_info.sin_family = AF_INET;
    conn_info.sin_port = htons(port);
    conn_info.sin_addr.s_addr = addr;

    socket_fd_ = socket(AF_INET, SOCK_STREAM, 0);

    if (bind(socket_fd_, (struct sockaddr*)&conn_info, sizeof(conn_info))) {
        std::ostringstream oss;
        oss << "Couldn't bind socket: " << std::strerror(errno);
        throw std::runtime_error(oss.str());
    }

    // Five-message queue is quite enough for testing
    listen(socket_fd_, 5);
}

std::string ServerSocket::Recieve() {
    constexpr static std::size_t kBufSize = 1024;
    char buffer[kBufSize] = "";
    recv(client_socket_, buffer, kBufSize, 0);
    return buffer;
}

constexpr static std::size_t kTestPort = 8080;
constexpr static in_addr_t kTestIP = INADDR_ANY;

bool SocketLogger() {
    ServerSocket serv_socket{kTestPort, kTestIP};

    logger::Logger logger{
            std::make_unique<Writer>(std::make_unique<WriteToSocket>(kTestPort, kTestIP)),
            LogLevel::Warn};
    serv_socket.Accept();

    logger.Log("info msg", LogLevel::Info);
    logger.Log("warn msg", LogLevel::Warn);

    logger.Stop();

    std::istringstream iss{serv_socket.Recieve()};
    // Skip timestamp
    std::string str;
    iss >> str;
    iss >> str;

    // Check log level
    iss >> str;
    if (str != "(WARN)") {
        std::cout << "Wrong log level: " << str << '\n';
        return false;
    }

    // Skip whitespace
    iss.ignore();

    // Check message
    std::getline(iss, str);
    if (str != "warn msg") {
        std::cout << "Wrong message: '" << str << "'\n";
        return false;
    }
    return true;
}
}  // namespace test::sockets
