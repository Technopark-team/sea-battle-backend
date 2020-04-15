#ifndef PROJECT_SERVER_SERVER_H
#define PROJECT_SERVER_SERVER_H

#include "IServer.h"

class Server: public IServer{
private:
    int m_socket;
public:
    Server(std::string host, std::string port, int sock) : IServer(std::move(host), std::move(port)), m_socket(sock) {}
    void run() override;
};


#endif //PROJECT_SERVER_SERVER_H
