#include <iostream>
#include <thread>
#include "EngineServer.h"

EngineServer::EngineServer(std::string host, uint32_t port):
                            Server(std::move(host), port) {
    m_engine = std::make_shared<Engine>();
    m_parser = std::make_shared<Parser>();
    m_session_manager = std::make_shared<SessionManager>();
}

int EngineServer::switch_action(std::string message, UserPtr user) {
    if (message.empty()) {
        // erase disconnected client // recv returns empty msg

        std::cout << "erase" << std::endl;
        clients.erase(user->get_id());

        //notifySession()

        return 1;
    }

    std::string response = "true";

    typeMsg type = m_parser->parse_type(message);
    if (type == typeMsg::CreateSession) {
        int id = m_parser->parseCreateSession(message);
        bool result = m_session_manager->create_session(user, id);
        if (result) {
            user->setSessionId(id);

            //std::cout << user->getSessionId() << std::endl;
        } else {

        }

        user->write(response);
    } else if (type == typeMsg::CreateUser) {
        user->set_name(m_parser->parseCreateUser(message));
    } else if (type == typeMsg::JoinSession) {
        int id = m_parser->parseJoinSession(message);
        m_session_manager->add_user_in_session(user, id);

    } else if (type == typeMsg::StartGame) {

    }
    return 0;
}



void EngineServer::do_accept() {
    while (true) {
        std::shared_ptr<ClientSocket> new_client = m_socket->accept_client();

        if (new_client && new_client->getFd() > -1) {
            std::cout << "new client's sd is " << new_client->getFd() << std::endl;

            auto read = std::bind(&EngineServer::asyncRead, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
            auto write = std::bind(&EngineServer::asyncWrite, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
            auto switchF = std::bind(&EngineServer::switch_action, this, std::placeholders::_1, std::placeholders::_2);

            std::shared_ptr<User> user = std::make_shared<User>(new_client, read, write, switchF);

            bool flag = clients.insert({user->get_id(), user}).second;

            user->read();
        }
        sleep(1);
        //break;
    }
}

void EngineServer::asyncRead(std::shared_ptr<ClientSocket> client, std::string& message, std::function<void(int)> callback) {
    Event event = Event(client, message, event::WantRead, callback);
    std::cout << " read" << std::endl;
    wantReadEvents.push_back(event);
}

void EngineServer::asyncWrite(std::shared_ptr<ClientSocket> client, std::string& message, std::function<void(int)> callback) {
    Event event = Event(client, message, event::WantWrite, callback);
    workEvents.push(event);
}

void EngineServer::run() {

    auto manageFunction = [this]() {
        m_engine->ManageClients(wantReadEvents, workEvents, mWantReadEvents, mWorkEvents);
    };

    auto processFunction = [this]() {
        this->process();
    };

    std::thread manageThread(manageFunction);
    std::thread processThread(processFunction);

    do_accept();

    manageThread.join();
    processThread.join();
}

void EngineServer::process() {
    while (true) {
        std::string msg;
        std::shared_ptr<ClientSocket> cl = std::make_shared<ClientSocket>(4, false);
        Event event (cl, msg, event::WantRead);

        {
            std::unique_lock<std::mutex> lock(mWorkEvents);
            if (workEvents.empty()) {
                lock.unlock();
                usleep(10000);
                continue;
            }
            event = workEvents.front();
            workEvents.pop();
        }

        if (event._status == event::WantRead) {

            int result = event.client->receive(msg);
            event._data.get().assign(msg);
            event.callback(errno);
        } else {
            event.client->send_msg(event._data.get());
            event.callback(errno);
        }

        //break;
    }
}

