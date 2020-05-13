#ifndef SEA_BATTLE_BACKEND_USER_INPUT_H
#define SEA_BATTLE_BACKEND_USER_INPUT_H

#include <memory>
#include "../sbcli/config/config.h"
#include "sbutils/data/data.h"
#include "ui_interface.h"

namespace seabattle {
namespace client {
namespace ui {

// TODO: добавить документацию к методам и свойствам

class AuthConsoleInput : public IUserInput {
 public:
    explicit AuthConsoleInput();
    ~AuthConsoleInput() = default;

    size_t ReadCommand(config::UserCommand &user_command) override;
    size_t ReadAuthData(utils::data::AuthData &auth_data);

};

}
}
}

#endif //SEA_BATTLE_BACKEND_USER_INPUT_H
