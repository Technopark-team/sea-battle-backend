#ifndef SEABATTLE_MENU_CONSOLE_INPUT_H
#define SEABATTLE_MENU_CONSOLE_INPUT_H

#include <memory>
#include <ncurses.h>
#include "sbcli/config/config.h"
#include "ui_interface.h"


namespace seabattle {
namespace client {
namespace ui {

// TODO: добавить документацию к методам и свойствам
// TODO: interface

class MenuConsoleInput {
 public:
    explicit MenuConsoleInput();
    ~MenuConsoleInput() = default;

    size_t RenderAuth(size_t &choice);
    size_t RenderNonAuth(size_t &choice);

private:
    size_t DrawMenuAuth(size_t item);
    size_t DrawMenuNonAuth(size_t item);
};

}  // namespace ui
}  // namespace client
}  // namespace seabattle

#endif  // SEABATTLE_MENU_CONSOLE_INPUT_H
