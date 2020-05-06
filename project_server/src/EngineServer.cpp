#include <iostream>
#include "EngineServer.h"

EngineServer::EngineServer(std::string host, uint32_t port):
                            Server(std::move(host), port) {
    m_engine = std::make_shared<Engine>();
    m_parser = std::make_shared<Parser>();
    m_session_manager = std::make_shared<SessionManager>();
}

int EngineServer::switch_action(std::string message, UserPtr user) {
    typeMsg type = m_parser->parse_type(message);

    /*if (type == typeMsg::CreateSession) {
        m_parser->parseCreateSession(message);

        m_session_manager->create_session(user, id);
    } else if (type == )*/
}



void EngineServer::do_accept() {
    while (true) {
        std::shared_ptr<ClientSocket> new_client = m_socket->accept_client();

        if (new_client && new_client->getFd() > -1) {
            std::cout << "new client's sd is " << new_client->getFd() << std::endl;
            std::shared_ptr<Connection> connection = std::make_shared<Connection>(new_client);
            auto f = std::bind(&EngineServer::asyncRead, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
            connection->read(f);
        }

        usleep(100);
        //break;
    }
}

void EngineServer::asyncRead(std::shared_ptr<ClientSocket> client, std::string message, std::function<void(int)> callback) {
    Event event = Event(client, message, event::WantRead, callback);
    work_events.push(event);
}

void EngineServer::asyncWrite(std::shared_ptr<ClientSocket> client, std::string message, std::function<void(int)> callback) {
    Event event = Event(client, message, event::WantWrite, callback);
    work_events.push(event);
}


void EngineServer::Connection::read(
        const std::function<void(std::shared_ptr<ClientSocket>, std::string, std::function<void(int)>)>& async_read)  {
    auto cb = [con = shared_from_this()](int error) {
        con->readHandler(error);
    };

    async_read(client, buffer, cb);
}

void EngineServer::Connection::readHandler(int error) {
    std::string message = buffer;
    UserPtr user = clients.find(client)->second;
    switch_action(message, user);


}

void EngineServer::Connection::write(
        const std::function<void(std::shared_ptr<ClientSocket>, std::string, std::function<void(int)>)>& async_write,
        const std::string &message) {

        buffer = message;
        auto cb = [con = shared_from_this()](int error) {
            con->writeHandler(error);
        };
        async_write(client, buffer, cb);
}

void EngineServer::Connection::writeHandler(int error) {

}

void EngineServer::process() {

}

