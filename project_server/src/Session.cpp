#include "Session.h"

size_t Session::next_id = 1;

Session::Session(UserPtr user): id(next_id++), started(0) {
    users.insert(user);
    game_engine = std::make_shared<IGameEngine>();
}


error Session::add_user_in_session(UserPtr user) {
    if (isFull()) {
        return error::Full;
    }
    if (users.insert(user).second) {
        return error::Success;
    }
    return error::UserExist;
}

error Session::startGame(UserPtr user, const Map& userMap) {
    if (!game_engine->insertMap(user->get_id(), userMap)) {
        return error::NotValidMap;
    }
    started++;
    if (started == 1) {
        return error::Wait;
    }

    game_engine->StartGame();
    game_engine->setStep(user->get_id());
    return error::Started;
}

void Session::notifyUsers(const std::string& message) {
    for (auto& user: users) {
        user->write(message);
    }
}


std::shared_ptr<GameState> Session::updateGameState(UserPtr user, const Point& point) {
    std::shared_ptr<GameState> gameState = game_engine->UpdateGame(user->get_id(), point);
    return gameState;
}

EraseState Session::eraseUser(UserPtr user) {
    game_engine->eraseId(user->get_id());
    users.erase(user);

    if (started == 2) {
        int winner_id = -1;
        game_engine->EndGame(user->get_id(), winner_id);
        started = 0;
        return EraseState(winner_id);
    }
    return EraseState();
}

size_t Session::GetId() {
    return id;
}
