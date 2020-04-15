#ifndef PROJECT_SERVER_SESSIONMANAGER_H
#define PROJECT_SERVER_SESSIONMANAGER_H

#include <memory>
#include <set>
#include "Session.h"


using SessionPtr = std::shared_ptr<Session>;

enum session_type {
    Multi = true,
    Local = false
};

class SessionManager {
public:
    SessionManager() = default;
    bool create_session(UserPtr user, size_t id, session_type flag = Multi);
    int update_sessions();
    int delete_session();
    int update_with_user_id(size_t user_id, std::string message);

    bool add_user_in_session(size_t session_id, UserPtr user);
private:
    std::set<SessionPtr> sessions;
};


#endif //PROJECT_SERVER_SESSIONMANAGER_H
