#include "ClientSocket.h"
#include <iostream>

int ClientSocket::receive(std::string& msg) {
    char buffer[1024];
    ssize_t n = 0;
    if (!msg.empty()) {
        msg.assign("");
    }

    while ((n = recv(getFd(), buffer, sizeof(buffer), 0)) > 0) {
        std::string temp_str(buffer, buffer + n);
        msg += temp_str;
    }

    if (msg.empty()) {
        return 0;
    }
    return 1;
}

int ClientSocket::send_msg(const std::string& msg) {
    int left = msg.size();
    ssize_t sent = 0;

    while (left > 0) {
        sent = send(getFd(), msg.data() + sent, msg.size() - sent, 0);
        if (sent == -1) {
            throw std::runtime_error("write failed: " + std::string(strerror(errno)));
        }
        left -= sent;
    }
    return 0;
}




