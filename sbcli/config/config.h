#ifndef SEA_BATTLE_BACKEND_CONFIG_H
#define SEA_BATTLE_BACKEND_CONFIG_H

#include <string>

namespace seabattle {
namespace client {
namespace config {

struct UserData {
    int user_id = 0;

    UserData() = default;
    UserData(int id) : user_id(id) {}
};

struct AuthData {
    std::string login{};
    std::string password{};

    AuthData() = default;
    AuthData(std::string log, std::string pass)
        : login(std::move(log)), password(std::move(password)) {}
};

struct UserCommand {
    std::string command{};

    UserCommand() = default;
    UserCommand(std::string com) : command(std::move(com)) {}
};

}  // namespace config
}  // namespace client
}  // namespace seabattle

#endif  // SEA_BATTLE_BACKEND_CONFIG_H
