#ifndef PROJECT_SERVER_ENGINE_H
#define PROJECT_SERVER_ENGINE_H


#include "IEngine.h"
#include "User.h"

enum event {
    WantWrite,
    Wait,
    WantRead
};

class Engine: public IEngine {
public:
    Engine(): IEngine() {}
    void ManageClients() override;
    int get_users_with_events(std::vector<UserPtr> users_events, std::vector<UserPtr> all_users);
    int get_diconnected_users(std::vector<UserPtr> disc_users) {
        return 0;
    }
};


#endif //PROJECT_SERVER_ENGINE_H
