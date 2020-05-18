#include "menu_console_input.h"

namespace seabattle {
namespace client {
namespace ui {

MenuConsoleInput::MenuConsoleInput() {}

size_t MenuConsoleInput::ReadCommand(config::UserCommand& user_command) {
    user_command.command = config::CLOSE_COMMAND;
    return 0;
}

}  // namespace ui
}  // namespace client
}  // namespace seabattle
