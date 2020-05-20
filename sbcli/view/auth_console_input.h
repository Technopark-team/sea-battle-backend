#ifndef SEA_BATTLE_BACKEND_USER_INPUT_H
#define SEA_BATTLE_BACKEND_USER_INPUT_H

#include <memory>
#include <ncurses.h>
#include <locale.h>
#include "sbcli/config/config.h"
#include "sbutils/data/data.h"
#include "ui_interface.h"

namespace seabattle {
namespace client {
namespace view {

// TODO: добавить документацию к методам и свойствам

class AuthConsoleInput {
 public:
    explicit AuthConsoleInput();
    ~AuthConsoleInput() = default;

    size_t ReadAuthData(utils::data::AuthData &auth_data);

    size_t RenderAuth(size_t &choice);
    size_t RenderNonAuth(size_t &choice);

 private:
    size_t DrawMenuAuth(size_t item);
    size_t DrawMenuNonAuth(size_t item);

};

}
}
}

#endif //SEA_BATTLE_BACKEND_USER_INPUT_H
