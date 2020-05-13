#ifndef SEA_BATTLE_BACKEND_CONFIG_H
#define SEA_BATTLE_BACKEND_CONFIG_H

#include <string>

namespace seabattle {
namespace client {
namespace config {

// TODO: добавить струтуру ip/port сервера

enum UserCommandId {
    EXIT_COMMAND = 1,
    SIGNIN_COMMAND,
    SIGNUP_COMMAND,
    MENU_COMMAND,
    SINGLE_COMMAND,
    LOAD_COMMAND,
    MULTI_COMMAND,
    STEP_COMMAND,
};

struct UserCommand {
    size_t command{};

    UserCommand() = default;
    UserCommand(size_t com) : command(com) {}
};

}  // namespace config
}  // namespace client
}  // namespace seabattle

#endif  // SEA_BATTLE_BACKEND_CONFIG_H
