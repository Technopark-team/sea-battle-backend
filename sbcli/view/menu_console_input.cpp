#include "menu_console_input.h"
#include <iostream>

namespace seabattle {
namespace client {
namespace view {

MenuConsoleInput::MenuConsoleInput() : main_menu_exist_(), main_menu_nonexist_() {}

size_t MenuConsoleInput::Run(size_t& choice, const config::UserStatus auth_status) {
    switch (auth_status) {
        case (config::UserStatus::AUTHORIZED):
//            main_menu_exist_.Render(choice);
            break;
        case (config::UserStatus::NOT_AUTHORIZED):
//            main_menu_nonexist_.Render(choice);
            break;
    }
    return 0;
}

}  // namespace view
}  // namespace client
}  // namespace seabattle
