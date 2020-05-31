#ifndef SEABATTLE_GAME_CONSOLE_INPUT_H
#define SEABATTLE_GAME_CONSOLE_INPUT_H

#include <memory>
#include "sbcli/config/config.h"
#include "sbcli/components/game/game.h"
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

 private:
    component::GameMenu game_menu_;
};

}
}
}


#endif  // SEABATTLE_GAME_CONSOLE_INPUT_H
