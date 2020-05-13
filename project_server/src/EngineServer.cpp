#include <iostream>
#include <thread>

#include "EngineServer.h"

EngineServer::EngineServer(std::string host, uint32_t port):
                            Server(std::move(host), port) {
    m_engine = std::make_shared<Engine>();
    m_parser = std::make_shared<Parser>();
    m_session_manager = std::make_shared<SessionManager>();
}

int EngineServer::switch_action(const std::string& message, UserPtr user) {
    std::string response = "true";

    if (message.empty()) {
        m_session_manager->eraseUser(user, user->getSessionId());
        // todo: real serializer
        response = "user_id: "+ std::to_string(user->get_id()) + " disconnected";
        m_session_manager->notifySession(response, user->getSessionId());

        needClose.push_back(user->get_client()->getFd());
        clients.erase(user->get_id());
        return 1;
    }

    typeMsg type = m_parser->parse_type(message);
    if (type == typeMsg::CreateSession) {
        // todo: real serializer and parser

        int id = m_parser->parseCreateSession(message);
        bool result = m_session_manager->create_session(user, id);

        if (result) {
            user->setSessionId(id);
            response = "session created " + std::to_string(id);
        } else {

        }

        m_session_manager->notifySession(response, id);
    } else if (type == typeMsg::CreateUser) {
        user->set_name(m_parser->parseCreateUser(message));


        user->write(response);
    } else if (type == typeMsg::JoinSession) {
        int id = m_parser->parseJoinSession(message);
        error result = m_session_manager->add_user_in_session(user, id);

        if (result == error::Success) {
            user->setSessionId(id);
            response = "joined to session " + std::to_string(id);
        }

        m_session_manager->notifySession(response, id);
    } else if (type == typeMsg::StartGame) {
        Map userMap = m_parser->parseStartGame(message);
        m_session_manager->startGame(user, userMap, user->getSessionId());


        m_session_manager->notifySession(response, user->getSessionId());
    } else if (type == typeMsg::UpdateGame) {
        Point point = m_parser->parseUpdateGame(message);
        std::shared_ptr<GameState> gameState = nullptr;
        m_session_manager->updateStep(user, point, user->getSessionId(), gameState);

        if (!gameState) {

        } else {
            //todo:serialize struct
        }
        m_session_manager->notifySession(response, user->getSessionId());
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

            clients.insert({user->get_id(), user}).second;

            user->read();
        }
        sleep(1);
    }
}

void EngineServer::asyncRead(std::shared_ptr<ClientSocket> client, std::string& message, std::function<void(int)> callback) {
    Event event = Event(client, message, event::WantRead, callback);

    auto result = std::find_if(wantReadEvents.begin(), wantReadEvents.end(), [&event](Event& ev){
        return event.client->getFd() == ev.client->getFd();});

    if (result == wantReadEvents.end()) {
        wantReadEvents.push_back(event);
    }
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
        process();
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
    }
}

