#include "game.h"

namespace seabattle {
namespace client {
namespace controller {

GameController::GameController(std::shared_ptr<network::TCPClient>& network_client)
    : game_model_(new model::GameModel(network_client)),
      game_console_interface_(new view::GameConsoleInput()) {}
size_t GameController::Action(std::shared_ptr<config::ControllerSignal>& controller_signal) {
    controller_signal->signal = config::Controller::NONE;
    return 0;
}
}  // namespace controller
}  // namespace client
}  // namespace seabattle