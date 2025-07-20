#include "writer/write_to_socket.h"

#include <cerrno>
#include <netinet/in.h>
#include <sstream>
#include <stdexcept>
#include <sys/socket.h>

namespace logger::writer {
WriteToSocket::WriteToSocket(unsigned short port, in_addr_t sin_addr) {
    sockaddr_in connection_info;
    connection_info.sin_family = AF_INET;
    connection_info.sin_port = htons(port);
    connection_info.sin_addr.s_addr = sin_addr;

    socket_desc_ = socket(AF_INET, SOCK_STREAM, 0);

    if (connect(socket_desc_, (struct sockaddr*)&connection_info, sizeof(connection_info))) {
        std::ostringstream oss;
        oss << "Couldn't connect to socket: " << std::to_string(errno);
        throw std::runtime_error(oss.str());
    }
}
}  // namespace logger::writer
