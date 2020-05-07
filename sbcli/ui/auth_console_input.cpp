#include "auth_console_input.h"

namespace seabattle {
namespace client {
namespace ui {

AuthConsoleInput::AuthConsoleInput() {}

size_t AuthConsoleInput::ReadCommand(config::UserCommand& user_command) {
    user_command.command = "menu";
    return 0;
}

size_t AuthConsoleInput::ReadAuthData(config::AuthData& auth_data) {
    auth_data.login = "log";
    auth_data.password = "pas";
    return 0;
}
}  // namespace ui
}  // namespace client
}  // namespace seabattle
