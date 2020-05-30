#include "Session.h"

size_t Session::next_id_ = 1;

Session::Session(UserPtr user): id_(next_id_++), started_(0) {
    users_.insert(user);
    game_engine_ = std::make_shared<IGameEngine>();
}


Error Session::AddUserInSession(UserPtr user) {
    if (IsFull()) {
        return Error::Full;
    }
    if (users_.insert(user).second) {
        return Error::Success;
    }
    return Error::UserExist;
}

Error Session::StartGame(UserPtr user, const Map& user_map) {
    if (!game_engine_->InsertMap(user->GetId(), user_map)) {
        return Error::NotValidMap;
    }
    started_++;
    if (started_ == 1) {
        return Error::Wait;
    }

    game_engine_->StartGame();
    game_engine_->SetStep(user->GetId());
    return Error::Started;
}

void Session::NotifyUsers(const std::string& message) {
    for (auto& user: users_) {
        user->write(message);
    }
}


std::shared_ptr<GameState> Session::UpdateGameState(UserPtr user, const Point& point) {
    std::shared_ptr<GameState> game_state = game_engine_->UpdateGame(user->GetId(), point);
    return game_state;
}

EraseState Session::EraseUser(UserPtr user) {
    game_engine_->EraseId(user->GetId());
    users_.erase(user);

    if (started_ == 2) {
        int winner_id = -1;
        game_engine_->EndGame(user->GetId(), winner_id);
        started_ = 0;
        return EraseState(winner_id);
    }
    return EraseState();
}

bool Session::IsFull() {
    return users_.size() >= 2;
}

size_t Session::GetId() {
    return id_;
}
