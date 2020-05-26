#ifndef PROJECT_SERVER_SESSION_H
#define PROJECT_SERVER_SESSION_H

#include <set>

#include "IGameEngine.h"
#include "User.h"



class Session {
private:
    static size_t next_id_;
    size_t id_;
    std::set<UserPtr> users_;
    size_t started_;
    std::shared_ptr<IGameEngine> game_engine_;
public:
    explicit Session(UserPtr user);

    Error AddUserInSession(UserPtr user);
    EraseState EraseUser(UserPtr user);

    Error StartGame(UserPtr user, const Map& user_map);
    std::shared_ptr<GameState> UpdateGameState(UserPtr user, const Point& point);

    void NotifyUsers(const std::string& message);

    bool IsFull();

    size_t GetId();
};

#endif //PROJECT_SERVER_SESSION_H
