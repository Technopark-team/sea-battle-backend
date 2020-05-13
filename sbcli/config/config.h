#ifndef SEA_BATTLE_BACKEND_CONFIG_H
#define SEA_BATTLE_BACKEND_CONFIG_H

#include <string>

namespace seabattle {
namespace client {
namespace config {

// TODO: добавить струтуру ip/port сервера

struct UserCommand {
    std::string command{};

    UserCommand() = default;
    UserCommand(std::string com) : command(std::move(com)) {}
};

}  // namespace config
}  // namespace client
}  // namespace seabattle

#endif  // SEA_BATTLE_BACKEND_CONFIG_H
