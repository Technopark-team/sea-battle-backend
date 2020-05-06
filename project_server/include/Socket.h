#ifndef PROJECT_SERVER_SOCKET_H
#define PROJECT_SERVER_SOCKET_H
#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>
#include <string>
#include <cstring>
#include <memory>
#include <arpa/inet.h>
#include <fcntl.h>

class Socket {
protected:
    int sock_fd;
public:
    Socket() noexcept(false) : sock_fd(-1){}
    explicit Socket(int socket): sock_fd(socket){};

    virtual ~Socket(){}

    void setNonBlocking(bool option) {
        int flags = fcntl(sock_fd, F_GETFL, 0);
        int new_flags = (option)? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
        if (fcntl(sock_fd, F_SETFL, new_flags) == -1) {
            throw std::runtime_error("make nonblocked: " + std::string(strerror(errno)));
        }
    }

    int getFd() {
        return sock_fd;
    }
};

#endif //PROJECT_SERVER_SOCKET_H
