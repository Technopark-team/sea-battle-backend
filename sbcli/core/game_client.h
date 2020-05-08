#ifndef SEA_BATTLE_BACKEND_GAME_CLIENT_H
#define SEA_BATTLE_BACKEND_GAME_CLIENT_H

#include <cstddef>
#include <memory>
#include <string>
#include "config/config.h"
#include "controller/auth.h"
#include "controller/menu.h"
#include "model/user_model.h"
#include "ui/auth_console_input.h"


namespace seabattle {
namespace client {
namespace game {

namespace net = boost::asio;            // from <boost/asio.hpp>

class GameClient {
 public:
    GameClient();
    size_t run();

 private:
    std::unique_ptr<controller::AuthController> auth_controller_;
    std::unique_ptr<controller::MenuController> menu_controller_;
    std::shared_ptr<network::TCPClient> network_client_;
    net::io_context ioc;
};

}  // namespace game
}  // namespace client
}  // namespace seabattle

#endif  // SEA_BATTLE_BACKEND_GAME_CLIENT_H
