#ifndef SEABATTLE_GAME_CONSOLE_INPUT_H
#define SEABATTLE_GAME_CONSOLE_INPUT_H
#include <memory>
#include "sbutils/data/data.h"
#include "sbcli/config/config.h"
#include "ui_interface.h"


namespace seabattle {
namespace client {
namespace ui {

// TODO: добавить документацию к методам и свойствам

class GameConsoleInput : public IUserInput {
 public:
    explicit GameConsoleInput();
    ~GameConsoleInput() = default;

    size_t ReadCommand(config::UserCommand &user_command) override;
    size_t ReadMap(utils::data::PlayerMap &player_map);
    size_t ReadStep(utils::data::UserStep &user_step);

};

}
}
}


#endif  // SEABATTLE_GAME_CONSOLE_INPUT_H
