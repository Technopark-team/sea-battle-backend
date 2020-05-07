#ifndef SEABATTLE_MENU_H
#define SEABATTLE_MENU_H

#include <memory>
#include "../sbcli/config/config.h"
#include "../sbcli/ui/menu_console_input.h"
#include "controller_interface.h"

namespace seabattle {
namespace client {
namespace controller {

/**
 * Controller for menu
 */
class MenuController : public IController {
 public:
    explicit MenuController();
    ~MenuController() = default;

    /**
     * This method for MenuController
     * @param user_command
     * @return
     */
    size_t Action(config::UserCommand &user_command) override;

 private:
    std::unique_ptr<ui::MenuConsoleInput> console_interface_;
};

}  // namespace controller
}  // namespace client
}  // namespace seabattle

#endif  // SEABATTLE_MENU_H
