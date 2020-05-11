#ifndef SEA_BATTLE_BACKEND_CONFIG_H
#define SEA_BATTLE_BACKEND_CONFIG_H

#include <string>

namespace seabattle {
namespace client {
namespace config {

// TODO: убрать перенесенные структуры
// TODO: добавить струтуру ip/port сервера

struct UserData {
    int user_id = 0;

    UserData() = default;
    UserData(int id) : user_id(id) {}
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
