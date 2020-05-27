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

class GameConsoleInput : public IUserInput {
 public:
    explicit GameConsoleInput();
    ~GameConsoleInput() = default;
    size_t Run(size_t &choice);

    size_t ReadCommand(config::UserCommand &user_command) override;
    size_t ReadMap(utils::data::TestMap &player_map);
    size_t ReadStep(utils::data::TestPoint &user_step);

 private:
    component::GameMenu<block::ShipsView> game_menu_;
};

}
}
}


#endif  // SEABATTLE_GAME_CONSOLE_INPUT_H
