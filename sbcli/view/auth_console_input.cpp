#include "auth_console_input.h"
#include <iostream>

namespace seabattle {
namespace client {
namespace view {

AuthConsoleInput::AuthConsoleInput() : auth_menu_exist_(), auth_menu_nonexist_() {}

size_t AuthConsoleInput::Run(size_t &choice, utils::data::AuthData &auth_data, const size_t auth_status) {
    switch (auth_status) {
        case (config::UserStatus::AUTHORIZED):
            auth_menu_exist_.Render(choice);
            break;
        case (config::UserStatus::NOT_AUTHORIZED):
            auth_menu_nonexist_.Render(choice);
            if (choice == 0) {
                char* login = new char(9);
                char* password = new char(9);

                auth_menu_nonexist_.ReadAuthData(login, 8, password, 8);
                auth_data.login.assign(login);
                auth_data.password.assign(password);

                delete login;
                delete password;
            }
            break;
    }
    return 0;
}
}  // namespace view
}  // namespace client
}  // namespace seabattle
