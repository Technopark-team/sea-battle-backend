#include "game.h"

namespace seabattle {
namespace client {
namespace controller {

GameController::GameController(std::shared_ptr<network::TCPClient>& network_client)
    : game_model_(new model::GameModel(network_client)),
      game_console_interface_(new view::GameConsoleInput()) {}

size_t GameController::Action(std::shared_ptr<config::ControllerSignal>& controller_signal) {
    controller_signal->Clean();

    utils::data::TestMap player_map;
    utils::data::TestPoint player_point;
    config::UserCommandId map_exit;
    config::UserCommandId step_exit;
    game_console_interface_->ReadMap(player_map, map_exit);
    game_console_interface_->ReadStep(player_point, step_exit);

    size_t command = -1;

    controller_signal->signal = config::Controller::NONE;
    return 0;
}
}  // namespace controller
}  // namespace client
}  // namespace seabattle