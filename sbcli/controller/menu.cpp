#include "menu.h"

namespace seabattle {
namespace client {
namespace controller {

MenuController::MenuController() : console_interface_(new ui::MenuConsoleInput()) {}
size_t MenuController::Action(config::UserCommand& user_command) {
    console_interface_->ReadCommand(user_command);
    return 0;
}
}  // namespace controller
}  // namespace client
}  // namespace seabattle