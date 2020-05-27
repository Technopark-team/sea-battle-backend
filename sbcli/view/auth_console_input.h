#ifndef SEA_BATTLE_BACKEND_USER_INPUT_H
#define SEA_BATTLE_BACKEND_USER_INPUT_H

#include <memory>
//#include <ncurses.h>
#include "sbcli/components/auth/auth.h"
#include "sbcli/config/config.h"
#include "sbcli/config/view.h"

namespace seabattle {
namespace client {
namespace view {

// TODO: добавить документацию к методам и свойствам

class AuthConsoleInput {
 public:
    explicit AuthConsoleInput();
    ~AuthConsoleInput() = default;

    size_t Run(size_t &choice, utils::data::TestAuthData &auth_data,
               const config::UserStatus auth_status);

 private:
    component::AuthMenu<config::AuthExistUser, config::HelpMainMenu> auth_menu_exist_;
    component::AuthMenu<config::AuthNonExistUser, config::HelpMainMenu> auth_menu_nonexist_;
};

}  // namespace view
}  // namespace client
}  // namespace seabattle

#endif  // SEA_BATTLE_BACKEND_USER_INPUT_H
