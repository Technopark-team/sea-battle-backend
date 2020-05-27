#ifndef SEABATTLE_GAME_H
#define SEABATTLE_GAME_H

#include <memory>
#include "sbcli/config/config.h"
#include "sbcli/view/game_console_input.h"
#include "sbcli/model/game_model.h"
#include "controller_interface.h"

namespace seabattle {
namespace client {
namespace controller {

class GameController : public IController {
 public:
    explicit GameController(std::shared_ptr<network::TCPClient> &network_client);
    ~GameController() = default;

    /**
     * This method takes user's cmd for single/multi/load/exit.
     * @param user_command stores single/multi/load/exit req from user
     * @return
     */
    size_t Action(std::shared_ptr<config::ControllerSignal> &controller_signal) override;

 private:
    /**
     * This prop is smart pointer to model::UserModel obj.
     */
    std::unique_ptr<model::GameModel> game_model_;

 /**
  * This prop is smart pointer to view::MenuConsoleInput.
  */
    std::unique_ptr<view::GameConsoleInput> game_console_interface_;
};

}
}
}

#endif  // SEABATTLE_GAME_H
