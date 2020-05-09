#include "SessionManager.h"

bool SessionManager::create_session(UserPtr user, size_t id, type flag) {
    SessionPtr newSession = std::make_shared<Session>(user, id);
    return sessions.insert({id, newSession}).second;
}

error SessionManager::add_user_in_session(UserPtr user, size_t id) {
    auto it = sessions.find(id);
    if (it == sessions.end()) {
        return error::NotFound;
    }
    if (it->second->add_user_in_session(user)) {
        return error::Success;
    }
    return error::Full;
}

int SessionManager::delete_session(size_t id) {
    sessions.erase(id);
    return 0;
}

int SessionManager::update_with_user_id(const std::string &message, size_t user_id) {
    return 0;
}


