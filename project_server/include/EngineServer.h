#ifndef PROJECT_SERVER_ENGINESERVER_H
#define PROJECT_SERVER_ENGINESERVER_H

#include <utility>

#include "Server.h"
#include "Parser.h"
#include "Engine.h"
#include "SessionManager.h"


class EngineServer: public Server {
private:
    std::shared_ptr<IEngine> m_engine;
    std::shared_ptr<IParser> m_parser;
    std::shared_ptr<SessionManager> m_session_manager;
protected:
    std::vector<UserPtr> clients;
public:
    EngineServer(std::string host, std::string port, int sock, const std::shared_ptr<SessionManager>& session_manager):
    Server(std::move(host), std::move(port), sock) {
        m_engine = std::make_shared<Engine>();
        m_parser = std::make_shared<Parser>();
        m_session_manager = session_manager;
    }
    void run() override{}
    int switch_action(std::string message, UserPtr user);
    void do_accept(){}
};


#endif //PROJECT_SERVER_ENGINESERVER_H
