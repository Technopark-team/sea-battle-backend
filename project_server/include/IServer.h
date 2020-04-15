#ifndef PROJECT_SERVER_ISERVER_H
#define PROJECT_SERVER_ISERVER_H

#include <string>
#include <utility>

class IServer {
private:
    std::string m_host;
    std::string m_port;
public:
    IServer(std::string  host, std::string  port) : m_host(std::move(host)), m_port(std::move(port)) {}
    virtual ~IServer() = default;
    virtual void run() = 0;
};


#endif //PROJECT_SERVER_ISERVER_H
