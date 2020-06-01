#include "auth_console_input.h"
#include <iostream>

namespace seabattle {
namespace client {
namespace view {

AuthConsoleInput::AuthConsoleInput() : auth_menu_exist_(), auth_menu_nonexist_() {}

size_t AuthConsoleInput::Run(size_t& choice, utils::data::TestAuthData& auth_data,
                             const config::UserStatus auth_status) {
    switch (auth_status) {
        case (config::UserStatus::AUTHORIZED):
            auth_menu_exist_.Render(choice);
            break;
        case (config::UserStatus::NOT_AUTHORIZED):
            auth_menu_nonexist_.Render(choice);
            if (choice == 0) {
                char* login_ = new char(9);
                char* password_ = new char(9);

                auth_menu_nonexist_.ReadAuthData(login_, 8, password_, 8);
                auth_data.login_.assign(login_);
                auth_data.password_.assign(password_);

                delete login_;
                delete password_;
            }
            break;
    }

    return 0;
}
}  // namespace view
}  // namespace client
}  // namespace seabattle
