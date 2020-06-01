#ifndef SEA_BATTLE_BACKEND_GAME_CLIENT_H
#define SEA_BATTLE_BACKEND_GAME_CLIENT_H

#include <cstddef>
#include <memory>
#include <string>
#include <locale.h>
#include "config/config.h"
#include "controller/auth.h"
#include "controller/menu.h"
#include "controller/game.h"

// TODO: добавить документацию к методам и свойствам

namespace seabattle {
namespace client {
namespace game {

namespace net = boost::asio;            // from <boost/asio.hpp>

class GameClient {
 public:
    GameClient(config::IpPort net_config, config::Debug debug);
    ~GameClient();
    size_t run();

 private:
    std::unique_ptr<controller::AuthController> auth_controller_;
    std::unique_ptr<controller::MenuController> menu_controller_;
    std::unique_ptr<controller::GameController> game_controller_;
    std::shared_ptr<network::TCPClient> network_client_;
    std::shared_ptr<config::ControllerSignal> controller_signal_;
    net::io_service ioc;
};

}  // namespace game
}  // namespace client
}  // namespace seabattle

#endif  // SEA_BATTLE_BACKEND_GAME_CLIENT_H
