#include "game_console_input.h"
#include <iostream>

namespace seabattle {
namespace client {
namespace view {

GameConsoleInput::GameConsoleInput() : game_menu_() {}


size_t GameConsoleInput::ReadMap(utils::data::TestMap& player_map, config::UserCommandId& exit) {
    game_menu_.GetMap(player_map, exit);

    return 0;
}

size_t GameConsoleInput::ReadStep(utils::data::TestPoint& user_step, config::UserCommandId &end_game) {
//    if (controller_signal->debug.dev_mode == config::DevMode::DEV) {
//        std::cout << "input x, y: ";
//        std::cin >> user_step.x_ >> user_step.y_;
//    } else {
        game_menu_.GetStep(user_step, end_game);
//    }
//    user_step.x_ = 1;
//    user_step.y_ = 1;

    return 0;
}

}  // namespace view
}  // namespace client
}  // namespace seabattle