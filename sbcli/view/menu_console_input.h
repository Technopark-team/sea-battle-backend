#ifndef SEABATTLE_MENU_CONSOLE_INPUT_H
#define SEABATTLE_MENU_CONSOLE_INPUT_H

#include <memory>
#include <ncurses.h>
#include "sbcli/config/view.h"
#include "sbcli/components/menu/menu.h"
#include "sbcli/config/config.h"

namespace seabattle {
namespace client {
namespace view {

// TODO: добавить документацию к методам и свойствам
// TODO: interface

class MenuConsoleInput {
 public:
    explicit MenuConsoleInput();
    ~MenuConsoleInput() = default;

    size_t Run(size_t &choice, const size_t auth_status);

private:
    component::MainMenu<config::MenuExistUser, config::HelpMainMenu> main_menu_exist_;
    component::MainMenu<config::MenuNonExistUser, config::HelpMainMenu> main_menu_nonexist_;
};

}  // namespace view
}  // namespace client
}  // namespace seabattle

#endif  // SEABATTLE_MENU_CONSOLE_INPUT_H
