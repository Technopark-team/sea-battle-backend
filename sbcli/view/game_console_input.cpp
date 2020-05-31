#include "game_console_input.h"

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

//    player_map.ships.at(0).start_.x_ = 0;
//    player_map.ships.at(0).start_.y_ = 0;
//    player_map.ships.at(0).end_.x_ = 3;
//    player_map.ships.at(0).end_.y_ = 0;
//
//    player_map.ships.at(1).start_.x_ = 5;
//    player_map.ships.at(1).start_.y_ = 0;
//    player_map.ships.at(1).end_.x_ = 7;
//    player_map.ships.at(1).end_.y_ = 0;
//
//    player_map.ships.at(2).start_.x_ = 9;
//    player_map.ships.at(2).start_.y_ = 0;
//    player_map.ships.at(2).end_.x_ = 9;
//    player_map.ships.at(2).end_.y_ = 2;
//
//    player_map.ships.at(3).start_.x_ = 9;
//    player_map.ships.at(3).start_.y_ = 4;
//    player_map.ships.at(3).end_.x_ = 9;
//    player_map.ships.at(3).end_.y_ = 5;
//
//    player_map.ships.at(4).start_.x_ = 9;
//    player_map.ships.at(4).start_.y_ = 7;
//    player_map.ships.at(4).end_.x_ = 9;
//    player_map.ships.at(4).end_.y_ = 8;
//
//    player_map.ships.at(5).start_.x_ = 6;
//    player_map.ships.at(5).start_.y_ = 9;
//    player_map.ships.at(5).end_.x_ = 7;
//    player_map.ships.at(5).end_.y_ = 9;
//
//    player_map.ships.at(6).start_.x_ = 4;
//    player_map.ships.at(6).start_.y_ = 9;
//    player_map.ships.at(6).end_.x_ = 4;
//    player_map.ships.at(6).end_.y_ = 9;
//
//    player_map.ships.at(7).start_.x_ = 2;
//    player_map.ships.at(7).start_.y_ = 9;
//    player_map.ships.at(7).end_.x_ = 2;
//    player_map.ships.at(7).end_.y_ = 9;
//
//    player_map.ships.at(8).start_.x_ = 0;
//    player_map.ships.at(8).start_.y_ = 9;
//    player_map.ships.at(8).end_.x_ = 0;
//    player_map.ships.at(8).end_.y_ = 9;
//
//    player_map.ships.at(9).start_.x_ = 0;
//    player_map.ships.at(9).start_.y_ = 7;
//    player_map.ships.at(9).end_.x_ = 0;
//    player_map.ships.at(9).end_.y_ = 7;
    return 0;
}

size_t GameConsoleInput::ReadStep(utils::data::TestPoint& user_step, config::UserCommandId &exit) {
    game_menu_.GetStep(user_step, exit);

//    user_step.x_ = 1;
//    user_step.y_ = 1;
    return 0;
}

}  // namespace view
}  // namespace client
}  // namespace seabattle