#include "menu.h"

namespace seabattle {
namespace client {
namespace controller {

MenuController::MenuController() : console_interface_(new view::MenuConsoleInput()) {}

size_t MenuController::Action(std::shared_ptr<config::ControllerSignal>& controller_signal) {
    size_t command = -1;
    config::UserStatus auth_status = controller_signal->auth_user_status;
    controller_signal->Clean();

    console_interface_->Run(command, auth_status);
    if (controller_signal->auth_user_status == config::UserStatus::AUTHORIZED) {
        switch (command) {
            case 0:
                controller_signal->command = config::UserCommandId::MULTI_COMMAND;
                controller_signal->signal = config::Controller::GAME;
                break;
            case 1:
                controller_signal->command = config::UserCommandId::CLOSE_COMMAND;
                controller_signal->signal = config::Controller::NONE;
                break;
        }
    } else {
        switch (command) {
            case 0:
                controller_signal->command = config::UserCommandId::SIGNIN_COMMAND;
                controller_signal->signal = config::Controller::AUTH;
                break;
            case 1:
                controller_signal->command = config::UserCommandId::SIGNUP_COMMAND;
                controller_signal->signal = config::Controller::AUTH;
                break;
            case 2:
                controller_signal->command = config::UserCommandId::CLOSE_COMMAND;
                controller_signal->signal = config::Controller::NONE;
                break;
        }
    }

    return 0;
}
}  // namespace controller
}  // namespace client
}  // namespace seabattle