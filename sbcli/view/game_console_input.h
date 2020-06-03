#ifndef SEABATTLE_GAME_CONSOLE_INPUT_H
#define SEABATTLE_GAME_CONSOLE_INPUT_H

#include <memory>
#include "sbcli/components/game/game.h"
#include "sbcli/config/config.h"
#include "ui_interface.h"

namespace seabattle {
namespace client {
namespace view {

// TODO: добавить документацию к методам и свойствам

class GameConsoleInput {
 public:
    explicit GameConsoleInput();
    ~GameConsoleInput() = default;

    size_t ReadMap(utils::data::TestMap &player_map, config::UserCommandId &exit);
    size_t ReadStep(utils::data::TestPoint &user_step, config::UserCommandId &end_game);
    size_t WriteEnemyState(utils::data::TestPoint enemy_step, utils::data::TestGameState game_state,
                           utils::data::TestEraseState erase_state);

 private:
    component::GameMenu game_menu_;
};

}  // namespace view
}  // namespace client
}  // namespace seabattle

#endif  // SEABATTLE_GAME_CONSOLE_INPUT_H
