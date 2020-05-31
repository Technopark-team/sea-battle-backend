#ifndef SEA_BATTLE_BACKEND_CONFIG_H
#define SEA_BATTLE_BACKEND_CONFIG_H

#include <string>
#include "sbutils/data/test_data.h"

namespace seabattle {
namespace client {
namespace config {

// TODO: добавить струтуру ip/port сервера

enum class UserCommandId {
    DEFAULT_COMMAND = -1,
    SIGNIN_COMMAND = 1,
    SIGNUP_COMMAND,
    INPUT_COMMAND,
    MENU_COMMAND,
    LOGOUT_COMMAND,
    CLOSE_COMMAND,
    SINGLE_COMMAND,
    LOAD_COMMAND,
    MULTI_COMMAND,
    STEP_COMMAND,
    QUITMAP_COMMAND,
    QUITCELL_COMMAND,
    READYCELL_COMMAND,
    ENDGAME_COMMAND,
};

enum class UserStatus {
    AUTHORIZED = 1,
    NOT_AUTHORIZED,
};

enum class Controller {
    DEFAULT = -1,
    AUTH = 1,
    MENU,
    GAME,
    NONE,
};

struct UserCommand {
    UserCommandId command = UserCommandId::DEFAULT_COMMAND;

    UserCommand() = default;
    UserCommand(UserCommandId com) : command(std::move(com)) {}
};

struct ControllerSignal {
    Controller signal = Controller::DEFAULT;
    UserStatus auth_user_status = UserStatus::NOT_AUTHORIZED;
    int user_id = -1;
    UserCommand command = UserCommand();

    ControllerSignal() = default;
    ControllerSignal(Controller signal) : signal(std::move(signal)) {}
    ControllerSignal(Controller signal, UserStatus auth_user_status, int user_id,
                     UserCommand command)
        : signal(signal),
          auth_user_status(std::move(auth_user_status)),
          user_id(std::move(user_id)),
          command(std::move(command)) {}

    void Clean() {
        signal = Controller::DEFAULT;
        command = UserCommand();
    }
};

}  // namespace config
}  // namespace client
}  // namespace seabattle

#endif  // SEA_BATTLE_BACKEND_CONFIG_H
