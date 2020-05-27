#include "game.h"

namespace seabattle {
namespace client {
namespace controller {

GameController::GameController(std::shared_ptr<network::TCPClient>& network_client)
    : game_model_(new model::GameModel(network_client)),
      game_console_interface_(new view::GameConsoleInput()) {}

size_t GameController::Action(std::shared_ptr<config::ControllerSignal>& controller_signal) {
    controller_signal->Clean();

    size_t command = -1;
    game_console_interface_->Run(command);
    switch(command) {
        case 0:

            break;
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:

            break;
        case 6:

            break;
        case 7:

            break;
        case 8:

            break;
        case 9:

            break;
    }

    controller_signal->signal = config::Controller::MENU;
    return 0;
}
}  // namespace controller
}  // namespace client
}  // namespace seabattle