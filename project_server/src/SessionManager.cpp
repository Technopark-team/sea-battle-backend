#include "SessionManager.h"

bool SessionManager::create_session(UserPtr user, size_t id) {
    SessionPtr newSession = std::make_shared<Session>(user, id);
    return sessions.insert({id, newSession}).second;
}

error SessionManager::add_user_in_session(UserPtr user, size_t id) {
    auto it = sessions.find(id);
    if (it == sessions.end()) {
        return error::NotFound;
    }
    return it->second->add_user_in_session(user);
}

bool SessionManager::delete_session(size_t id) {
    return sessions.erase(id);
}


error SessionManager::startGame(UserPtr user, const Map& userMap, size_t id) {
    auto it = sessions.find(id);
    if (it == sessions.end()) {
        return error::NotFound;
    }
    it->second->startGame(user, userMap);
}

int SessionManager::updateStep(UserPtr user, const Point& point, size_t id) {
    auto iterator = sessions.find(id);

    iterator->second->updateGameState(user, point);
    return 0;
}

void SessionManager::notifySession(const std::string &message, size_t id) {
    auto iterator = sessions.find(id);
    if (iterator != sessions.end()) {
        iterator->second->notifyUsers(message);
    }
}

bool SessionManager::eraseUser(UserPtr user, size_t sessionId) {
    auto iterator = sessions.find(sessionId);
    if (iterator != sessions.end()){
        iterator->second->eraseUser(user);
        return true;
    }
    return false;
}



