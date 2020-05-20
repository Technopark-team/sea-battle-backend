#include "menu.h"
#include <iostream>

namespace seabattle {
namespace client {
namespace controller {

MenuController::MenuController() : console_interface_(new view::MenuConsoleInput()) {}
size_t MenuController::Action(std::shared_ptr<config::ControllerSignal>& controller_signal) {
//    console_interface_->ReadCommand(user_command);
    size_t auth_status = controller_signal->auth_user_status;
    std::cout << controller_signal->user_data.user_id << std::endl;
    controller_signal->Clean();
    size_t command;
    if (controller_signal->auth_user_status == config::UserStatus::AUTHORIZED) {
        console_interface_->RenderAuth(command);
        switch (command) {
            case 0:
                controller_signal->command = config::UserCommandId::SINGLE_COMMAND;
                controller_signal->signal = config::Controller::GAME;
                break;
            case 1:
                controller_signal->command = config::UserCommandId::LOAD_COMMAND;
                controller_signal->signal = config::Controller::GAME;
                break;
            case 2:
                controller_signal->command = config::UserCommandId::MULTI_COMMAND;
                controller_signal->signal = config::Controller::GAME;
                break;
            case 3:
                controller_signal->command = config::UserCommandId::LOGOUT_COMMAND;
                controller_signal->signal = config::Controller::AUTH;
                break;
            case 4:
                controller_signal->command = config::UserCommandId::CLOSE_COMMAND;
                controller_signal->signal = config::Controller::NONE;
                break;
        }
    } else {
        console_interface_->RenderNonAuth(command);
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