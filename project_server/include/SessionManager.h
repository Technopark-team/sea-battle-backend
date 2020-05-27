#ifndef PROJECT_SERVER_SESSIONMANAGER_H
#define PROJECT_SERVER_SESSIONMANAGER_H

#include <memory>
#include <map>

#include "Session.h"

using SessionPtr = std::shared_ptr<Session>;


class SessionManager {
public:
    SessionManager() = default;

    size_t CreateSession(UserPtr user);
    Error AddUserInSession(UserPtr user, size_t id);
    bool DeleteSession(size_t id);
    std::shared_ptr<EraseState> EraseUser(UserPtr user, size_t session_id);

    Error StartGame(UserPtr user, const Map& map, size_t id);
    void UpdateStep(UserPtr user, const Point& point, size_t id, std::shared_ptr<GameState>& game_state);

    void NotifySession(const std::string& message, size_t id);
private:
    std::map<int, SessionPtr> sessions_;
};


#endif //PROJECT_SERVER_SESSIONMANAGER_H
