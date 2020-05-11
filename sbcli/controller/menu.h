#ifndef SEABATTLE_MENU_H
#define SEABATTLE_MENU_H

#include <memory>
#include "../sbcli/config/config.h"
#include "../sbcli/ui/menu_console_input.h"
#include "controller_interface.h"

namespace seabattle {
namespace client {
namespace controller {

// TODO: добавить View для отображения меню с функцией render(some_data = null)

/**
 * Controller for user menu. It provides several choises for user: Single Game, Multiplayer Game,
 * Load Game, Exit.
 */
class MenuController : public IController {
 public:
    explicit MenuController();
    ~MenuController() = default;

    /**
     * This method takes user's cmd for single/multi/load/exit.
     * @param user_command stores single/multi/load/exit req from user
     * @return
     */
    size_t Action(config::UserCommand &user_command) override;

 private:
    /**
     * This prop is smart pointer to ui::MenuConsoleInput.
     */
    std::unique_ptr<ui::MenuConsoleInput> console_interface_;
};

}  // namespace controller
}  // namespace client
}  // namespace seabattle

#endif  // SEABATTLE_MENU_H
