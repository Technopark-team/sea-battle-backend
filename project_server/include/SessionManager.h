#ifndef PROJECT_SERVER_SESSIONMANAGER_H
#define PROJECT_SERVER_SESSIONMANAGER_H

#include <memory>
#include <map>

#include "Session.h"
#include "User.h"

using SessionPtr = std::shared_ptr<Session>;

enum class type {
    Multi = true,
    Local = false
};

enum class error {
    Success = 0,
    NotFound,
    Full
};

class SessionManager {
public:
    SessionManager() = default;
    bool create_session(UserPtr user, size_t id, type flag = type::Multi);
    error add_user_in_session(UserPtr user, size_t id);

    int delete_session(size_t id);
    int update_with_user_id(const std::string& message, size_t user_id);

private:
    std::map<int, SessionPtr> sessions;
};


#endif //PROJECT_SERVER_SESSIONMANAGER_H
