#ifndef SEA_BATTLE_BACKEND_CONFIG_H
#define SEA_BATTLE_BACKEND_CONFIG_H

#include <string>
#include "sbutils/data/data.h"

namespace seabattle {
namespace client {
namespace config {

// TODO: добавить струтуру ip/port сервера

enum UserCommandId {
    SIGNIN_COMMAND = 1,
    SIGNUP_COMMAND,
    MENU_COMMAND,
    LOGOUT_COMMAND,
    CLOSE_COMMAND,
    SINGLE_COMMAND,
    LOAD_COMMAND,
    MULTI_COMMAND,
    STEP_COMMAND,
};

enum UserStatus {
    AUTHORIZED = 1,
    NOT_AUTHORIZED,
};

enum Controller {
    AUTH = 1,
    MENU,
    GAME,
    NONE,
};

struct UserCommand {
    size_t command{};

    UserCommand() = default;
    UserCommand(size_t com) : command(com) {}
};

struct ControllerSignal {
    size_t signal = -1;
    size_t auth_user_status = -1;
    utils::data::UserData user_data = utils::data::UserData();
    UserCommand command = UserCommand();

    ControllerSignal() = default;
    ControllerSignal(size_t signal) : signal(signal) {}
    ControllerSignal(size_t signal, size_t auth_user_status, utils::data::UserData user_data,
                     UserCommand command)
        : signal(signal),
          auth_user_status(auth_user_status),
          user_data(std::move(user_data)),
          command(std::move(command)) {}

    void Clean() {
        signal = -1;
        command = UserCommand();
    }
};

}  // namespace config
}  // namespace client
}  // namespace seabattle

#endif  // SEA_BATTLE_BACKEND_CONFIG_H
