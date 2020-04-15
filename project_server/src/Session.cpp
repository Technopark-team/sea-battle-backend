#include "Session.h"

Session::Session(UserPtr user, size_t id): id(id){

}

int Session::recieve_from_player(std::string message) {
    return 0;
}

int Session::notify_users() {
    return 0;
}
