#ifndef PROJECT_SERVER_SESSION_H
#define PROJECT_SERVER_SESSION_H

#include <set>

#include "IGameEngine.h"
#include "User.h"



class Session {
private:
    static size_t next_id;
    size_t id;
    std::set<UserPtr> users;
    size_t started;
    std::shared_ptr<IGameEngine> game_engine;
public:
    explicit Session(UserPtr user);

    Error add_user_in_session(UserPtr user);
    EraseState eraseUser(UserPtr user);

    Error startGame(UserPtr user, const Map& userMap);
    std::shared_ptr<GameState> updateGameState(UserPtr user, const Point& point);

    void notifyUsers(const std::string& message);

    bool isFull() {
        return users.size() >= 2;
    }

    size_t GetId();
};

#endif //PROJECT_SERVER_SESSION_H
