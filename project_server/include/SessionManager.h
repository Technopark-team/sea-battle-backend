#ifndef PROJECT_SERVER_SESSIONMANAGER_H
#define PROJECT_SERVER_SESSIONMANAGER_H

#include <memory>
#include <map>

#include "Session.h"

using SessionPtr = std::shared_ptr<Session>;


class SessionManager {
public:
    SessionManager() = default;

    bool create_session(UserPtr user, size_t id);
    error add_user_in_session(UserPtr user, size_t id);
    bool delete_session(size_t id);
    bool eraseUser(UserPtr user, size_t sessionId);

    error startGame(UserPtr user, const Map& map, size_t id);
    int updateStep(UserPtr user, const Point& point, size_t id);

    void notifySession(const std::string& message, size_t id);
private:
    std::map<int, SessionPtr> sessions;
};


#endif //PROJECT_SERVER_SESSIONMANAGER_H
