#ifndef PROJECT_SERVER_ENGINESERVER_H
#define PROJECT_SERVER_ENGINESERVER_H

#include <utility>
#include <queue>
#include <unordered_map>

#include "Server.h"
#include "Parser.h"
#include "Engine.h"
#include "SessionManager.h"
#include "../DBAccess/include/DBAccess.h"

class EngineServer: public Server {
private:
    std::shared_ptr<IEngine> m_engine;
    std::shared_ptr<IParser> m_parser;
    std::shared_ptr<SessionManager> m_session_manager;
    std::shared_ptr<DBAccess> access_object;

    std::mutex mWantReadEvents;
    std::mutex mWorkEvents;

    void asyncRead(std::shared_ptr<ClientSocket> client, std::string& message, std::function<void(int)> callback);
    void asyncWrite(std::shared_ptr<ClientSocket> client, std::string& message, std::function<void(int)> callback);

    void do_accept();
    void process();

    std::vector<int> needClose;
protected:
    std::unordered_map<int, UserPtr> clients;
    std::vector<Event> wantReadEvents;
    std::queue<Event> workEvents;
public:
    EngineServer(std::string host, uint32_t port);
    ~EngineServer() {
        for (auto& sock: needClose) {
            close(sock);
        }
    }
    void run() override;
    int switch_action(const std::string& message, UserPtr user);
};


#endif //PROJECT_SERVER_ENGINESERVER_H
