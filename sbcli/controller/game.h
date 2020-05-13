#ifndef SEABATTLE_GAME_H
#define SEABATTLE_GAME_H

#include <memory>
#include "sbcli/config/config.h"
#include "sbcli/ui/game_console_input.h"
#include "sbcli/model/game_model.h"
#include "controller_interface.h"

namespace seabattle {
namespace client {
namespace controller {

class GameController : public IController {
 public:
    explicit GameController();
    ~GameController() = default;

    /**
     * This method takes user's cmd for single/multi/load/exit.
     * @param user_command stores single/multi/load/exit req from user
     * @return
     */
    size_t Action(config::UserCommand &user_command) override;

 private:
    /**
     * This prop is smart pointer to model::UserModel obj.
     */
    std::unique_ptr<model::GameModel> game_model_;

 /**
  * This prop is smart pointer to ui::MenuConsoleInput.
  */
    std::unique_ptr<ui::GameConsoleInput> game_console_interface_;
};

}
}
}

#endif  // SEABATTLE_GAME_H
