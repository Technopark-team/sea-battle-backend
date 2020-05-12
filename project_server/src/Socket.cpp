#include "Socket.h"

void Socket::setNonBlocking(bool option) {
    int flags = fcntl(sock_fd, F_GETFL, 0);
    int new_flags = (option)? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
    if (fcntl(sock_fd, F_SETFL, new_flags) == -1) {
        throw std::runtime_error("make nonblocked: " + std::string(strerror(errno)));
    }
}

int Socket::getFd() {
    return sock_fd;
}
