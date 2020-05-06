#ifndef PROJECT_SERVER_CLIENTSOCKET_H
#define PROJECT_SERVER_CLIENTSOCKET_H


#include "Socket.h"

class ClientSocket: public Socket {
public:
    explicit ClientSocket(int socket): Socket(socket) {
        setNonBlocking(true);
    }

    std::string receive(std::string& msg);
    int send_msg(const std::string& msg);
};


#endif //PROJECT_SERVER_CLIENTSOCKET_H
