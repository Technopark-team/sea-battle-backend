#ifndef PROJECT_SERVER_ENGINESERVER_H
#define PROJECT_SERVER_ENGINESERVER_H

#include <utility>
#include <queue>
#include <map>

#include "Server.h"
#include "Parser.h"
#include "Engine.h"
#include "SessionManager.h"
#include "Connection.h"


class EngineServer: public Server {
private:
    std::shared_ptr<IEngine> m_engine;
    inline static std::shared_ptr<IParser> m_parser;
    inline static std::shared_ptr<SessionManager> m_session_manager;

    class Connection: public std::enable_shared_from_this<Connection> {
        private:
            std::string buffer;
            std::shared_ptr<ClientSocket> client;

            void readHandler(int error);
            void writeHandler(int error);
        public:
            explicit Connection(std::shared_ptr<ClientSocket> client): client(std::move(client)) {
            }
            void read(const std::function<void(std::shared_ptr<ClientSocket>, std::string, std::function<void(int)>)>& async_read);
            void write(const std::function<void(std::shared_ptr<ClientSocket>, std::string, std::function<void(int)>)>& async_write, const std::string& message);
        };

    void asyncRead(std::shared_ptr<ClientSocket> client, std::string message, std::function<void(int)> callback);
    void asyncWrite(std::shared_ptr<ClientSocket> client, std::string message, std::function<void(int)> callback);
protected:
    static std::map<std::shared_ptr<ClientSocket>, UserPtr> clients;
    std::queue<Event> work_events;
public:
    EngineServer(std::string host, uint32_t port);
    void run() override{}
    static int switch_action(std::string message, UserPtr user);
    void do_accept();
};






#endif //PROJECT_SERVER_ENGINESERVER_H
