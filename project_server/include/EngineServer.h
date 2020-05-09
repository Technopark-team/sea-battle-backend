#ifndef PROJECT_SERVER_ENGINESERVER_H
#define PROJECT_SERVER_ENGINESERVER_H

#include <utility>
#include <queue>
#include <unordered_map>

#include "Server.h"
#include "Parser.h"
#include "Engine.h"
#include "SessionManager.h"


class EngineServer: public Server {
private:
    std::shared_ptr<IEngine> m_engine;
    std::shared_ptr<Parser> m_parser;
    std::shared_ptr<SessionManager> m_session_manager;

    std::mutex mWantReadEvents;
    std::mutex mWorkEvents;

    void asyncRead(std::shared_ptr<ClientSocket> client, std::string& message, std::function<void(int)> callback);
    void asyncWrite(std::shared_ptr<ClientSocket> client, std::string& message, std::function<void(int)> callback);

    void do_accept();
    void process();



protected:
    std::unordered_map<int, UserPtr> clients;
    std::vector<Event> wantReadEvents;
    std::queue<Event> workEvents;
public:
    EngineServer(std::string host, uint32_t port);
    void run() override;
    int switch_action(std::string message, UserPtr user);
};






#endif //PROJECT_SERVER_ENGINESERVER_H
