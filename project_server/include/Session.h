#ifndef PROJECT_SERVER_SESSION_H
#define PROJECT_SERVER_SESSION_H

#include "User.h"
#include <set>
#include "IGameEngine.h"

class Session {
private:
    size_t id;
    std::set<UserPtr> users;
    std::shared_ptr<IGameEngine> game_engine;
public:
    Session(UserPtr user, size_t id);

    int update();
    int recieve_from_player(std::string message);
    int update_game_state();
    int notify_users();
    bool add_user_in_session(UserPtr user) {
        return false;
    }
};


#endif //PROJECT_SERVER_SESSION_H
