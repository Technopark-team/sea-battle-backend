#include "Session.h"


Session::Session(UserPtr user, size_t id): id(id), started(0) {
    users.insert(user);
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

    started++;
    if (started == 1) {
        return error::Wait;
    }
    return error::Started;
}

void Session::notifyUsers(const std::string& message) {
    for (auto& user: users) {
        user->write(message);
    }
}

int Session::updateGameState(UserPtr user, const Point& point) {

    return 0;
}
