#include "game_console_input.h"
#include <iostream>

namespace seabattle {
namespace client {
namespace view {

GameConsoleInput::GameConsoleInput() : game_menu_() {}

/*
 *   0  1  2  3  4  5  6  7  8  9
 *  ┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼
 * 0│1▓│1▓│1▓│1▓│  │1▓│1▓│1▓│  │2▓│
 *  ┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼
 * 1│  │  │  │  │  │  │  │  │  │2▓│
 *  ┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼
 * 2│  │  │  │  │  │  │  │  │  │2▓│
 *  ┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼
 * 3│  │  │  │  │  │  │  │  │  │  │
 *  ┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼
 * 4│  │  │  │  │  │  │  │  │  │1▓│
 *  ┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼
 * 5│  │  │  │  │  │  │  │  │  │1▓│
 *  ┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼
 * 6│  │  │  │  │  │  │  │  │  │  │
 *  ┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼
 * 7│  │  │  │  │  │  │  │  │  │2▓│
 *  ┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼
 * 8│4▓│  │  │  │  │  │  │  │  │2▓│
 *  ┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼
 * 9│  │3▓│  │2▓│  │1▓│  │3▓│3▓│  │
 *  ┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼
 */

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