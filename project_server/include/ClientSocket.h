#ifndef PROJECT_SERVER_CLIENTSOCKET_H
#define PROJECT_SERVER_CLIENTSOCKET_H


#include "Socket.h"

class ClientSocket: public Socket {
public:
    explicit ClientSocket(int socket, bool option = true): Socket(socket) {
        if (option) {
            setNonBlocking(true);
        }
    }

    ~ClientSocket() = default;
    int receive(std::string& msg);
    int send_msg(const std::string& msg);

};


#endif //PROJECT_SERVER_CLIENTSOCKET_H
