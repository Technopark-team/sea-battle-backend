#ifndef SEABATTLE_MENU_CONSOLE_INPUT_H
#define SEABATTLE_MENU_CONSOLE_INPUT_H

#include <memory>
#include "../sbcli/config/config.h"
#include "ui_interface.h"

namespace seabattle {
namespace client {
namespace ui {

class MenuConsoleInput : public IUserInput {
 public:
    explicit MenuConsoleInput();
    ~MenuConsoleInput() = default;

    size_t ReadCommand(config::UserCommand &user_command) override;
};

}  // namespace ui
}  // namespace client
}  // namespace seabattle

#endif  // SEABATTLE_MENU_CONSOLE_INPUT_H
