#ifndef PROJECT_SERVER_ENGINE_H
#define PROJECT_SERVER_ENGINE_H


#include <utility>
#include <functional>
#include <queue>

#include "IEngine.h"
#include "User.h"
#include "ClientSocket.h"
#include "ClientSocket.h"

enum class event {
    WantWrite,
    Wait,
    WantRead
};

struct Event {
    Event(std::shared_ptr<ClientSocket> cl, std::string& data, event status):client(std::move(cl)), _data(data), _status(status) {
    }
    Event(std::shared_ptr<ClientSocket> cl, std::string& data, event status, std::function<void (int)> cb): client(std::move(cl)), _data(data), _status(status), callback(cb) {}

    Event& operator= (const Event& rhs) {
        client = rhs.client;
        _data = std::ref(rhs._data);
        callback = rhs.callback;
        _status = rhs._status;
        return *this;
    }

    event _status;
    std::shared_ptr<ClientSocket> client;
    std::reference_wrapper<std::string> _data;
    std::function<void (int)> callback;
};



class Engine: public IEngine {
public:
    Engine(): IEngine() {}
    void ManageClients() override;
    int get_users_with_events(std::vector<Event> users_events, std::queue<Event> all_users);
    int get_diconnected_users(std::vector<Event> disc_users) {
        return 0;
    }
};


#endif //PROJECT_SERVER_ENGINE_H
