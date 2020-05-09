#include "ServerSocket.h"

#include "Socket.h"

ServerSocket::ServerSocket(const std::string& host, uint32_t port) noexcept(false) {
    sock_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock_fd <=0) {
        throw std::runtime_error("socket: " + std::string(strerror(errno)));
    }

    int yes = 1;
    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        close(sock_fd);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(port);

    if (bind(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        close(sock_fd);
        throw std::runtime_error("bind: " + std::string(strerror(errno)));
    }

    listen(getFd(), 1000);
}


std::shared_ptr<ClientSocket> ServerSocket::accept_client() {
    struct sockaddr_in client;
    memset(&client, 0, sizeof(client));
    socklen_t client_len = sizeof(client);

    int client_sd = accept(getFd(), (struct sockaddr*)&client, &client_len);
    if (client_sd == -1) {
        return std::shared_ptr<ClientSocket>();
    }
    return std::make_shared<ClientSocket>(client_sd);
}
