#ifndef PROJECT_SERVER_SESSION_H
#define PROJECT_SERVER_SESSION_H

#include <set>

#include "IGameEngine.h"
#include "User.h"

enum class error {
    Success = 0,
    NotFound,
    Full,
    UserExist,
    Started,
    Wait
};

struct Ship {
    size_t start;
    size_t end;

    bool horizontal;
};

struct Map {
    std::vector<Ship> ships;
};

struct Point {
    size_t x;
    size_t y;
};


class Session {
private:
    size_t id;
    std::set<UserPtr> users;
    size_t started;
    std::shared_ptr<IGameEngine> game_engine;
public:
    Session(UserPtr user, size_t id);

    error add_user_in_session(UserPtr user);

    error startGame(UserPtr user, const Map& userMap);
    int updateGameState(UserPtr user, const Point& point);

    void notifyUsers(const std::string& message);

    bool isFull() {
        return users.size() >= 2;
    }
};

#endif //PROJECT_SERVER_SESSION_H
