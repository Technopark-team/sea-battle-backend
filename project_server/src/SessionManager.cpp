#include "SessionManager.h"

size_t SessionManager::create_session(UserPtr user) {
    SessionPtr newSession = std::make_shared<Session>(user);
    sessions.insert({newSession->GetId(), newSession});
    return newSession->GetId();
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
    error result = it->second->startGame(user, userMap);
    return result;
}

void SessionManager::updateStep(UserPtr user, const Point& point, size_t id, std::shared_ptr<GameState>& gameState) {
    auto iterator = sessions.find(id);
    gameState = iterator->second->updateGameState(user, point);
}

void SessionManager::notifySession(const std::string &message, size_t id) {
    auto iterator = sessions.find(id);
    if (iterator != sessions.end()) {
        iterator->second->notifyUsers(message);
    }
}

std::shared_ptr<EraseState> SessionManager::eraseUser(UserPtr user, size_t sessionId) {
    auto iterator = sessions.find(sessionId);
    if (iterator == sessions.end()) {
        return nullptr;
    }

    EraseState result = iterator->second->eraseUser(user);
    std::shared_ptr<EraseState> result_ptr = std::make_shared<EraseState>(result.started, result.winner_id);
    return result_ptr;
}
