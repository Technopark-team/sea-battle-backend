#include "game_console_input.h"

namespace seabattle {
namespace client {
namespace ui {

GameConsoleInput::GameConsoleInput() {}

size_t GameConsoleInput::ReadCommand(config::UserCommand& user_command) {
    user_command.command = config::STEP_COMMAND;
    return 0;
}

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

size_t GameConsoleInput::ReadMap(utils::data::PlayerMap& player_map) {
    player_map.ships.at(utils::data::SHIP4).begin_coordinate.x = 0;
    player_map.ships.at(utils::data::SHIP4).begin_coordinate.y = 0;
    player_map.ships.at(utils::data::SHIP4).end_coordinate.x = 3;
    player_map.ships.at(utils::data::SHIP4).end_coordinate.y = 0;

    player_map.ships.at(utils::data::SHIP3_1).begin_coordinate.x = 5;
    player_map.ships.at(utils::data::SHIP3_1).begin_coordinate.y = 0;
    player_map.ships.at(utils::data::SHIP3_1).end_coordinate.x = 7;
    player_map.ships.at(utils::data::SHIP3_1).end_coordinate.y = 0;

    player_map.ships.at(utils::data::SHIP3_2).begin_coordinate.x = 9;
    player_map.ships.at(utils::data::SHIP3_2).begin_coordinate.y = 0;
    player_map.ships.at(utils::data::SHIP3_2).end_coordinate.x = 9;
    player_map.ships.at(utils::data::SHIP3_2).end_coordinate.y = 2;

    player_map.ships.at(utils::data::SHIP2_1).begin_coordinate.x = 9;
    player_map.ships.at(utils::data::SHIP2_1).begin_coordinate.y = 4;
    player_map.ships.at(utils::data::SHIP2_1).end_coordinate.x = 9;
    player_map.ships.at(utils::data::SHIP2_1).end_coordinate.y = 5;

    player_map.ships.at(utils::data::SHIP2_2).begin_coordinate.x = 9;
    player_map.ships.at(utils::data::SHIP2_2).begin_coordinate.y = 7;
    player_map.ships.at(utils::data::SHIP2_2).end_coordinate.x = 9;
    player_map.ships.at(utils::data::SHIP2_2).end_coordinate.y = 8;

    player_map.ships.at(utils::data::SHIP2_3).begin_coordinate.x = 6;
    player_map.ships.at(utils::data::SHIP2_3).begin_coordinate.y = 9;
    player_map.ships.at(utils::data::SHIP2_3).end_coordinate.x = 7;
    player_map.ships.at(utils::data::SHIP2_3).end_coordinate.y = 9;

    player_map.ships.at(utils::data::SHIP1_1).begin_coordinate.x = 4;
    player_map.ships.at(utils::data::SHIP1_1).begin_coordinate.y = 9;
    player_map.ships.at(utils::data::SHIP1_1).end_coordinate.x = 4;
    player_map.ships.at(utils::data::SHIP1_1).end_coordinate.y = 9;

    player_map.ships.at(utils::data::SHIP1_2).begin_coordinate.x = 2;
    player_map.ships.at(utils::data::SHIP1_2).begin_coordinate.y = 9;
    player_map.ships.at(utils::data::SHIP1_2).end_coordinate.x = 2;
    player_map.ships.at(utils::data::SHIP1_2).end_coordinate.y = 9;

    player_map.ships.at(utils::data::SHIP1_3).begin_coordinate.x = 0;
    player_map.ships.at(utils::data::SHIP1_3).begin_coordinate.y = 9;
    player_map.ships.at(utils::data::SHIP1_3).end_coordinate.x = 0;
    player_map.ships.at(utils::data::SHIP1_3).end_coordinate.y = 9;

    player_map.ships.at(utils::data::SHIP1_4).begin_coordinate.x = 0;
    player_map.ships.at(utils::data::SHIP1_4).begin_coordinate.y = 7;
    player_map.ships.at(utils::data::SHIP1_4).end_coordinate.x = 0;
    player_map.ships.at(utils::data::SHIP1_4).end_coordinate.y = 7;
    return 0;
}

size_t GameConsoleInput::ReadStep(utils::data::UserStep& user_step) {
    user_step.user_id = 1;
    user_step.step.x = 1;
    user_step.step.y = 1;
    return 0;
}

}  // namespace ui
}  // namespace client
}  // namespace seabattle
