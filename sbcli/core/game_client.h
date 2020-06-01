#ifndef SEA_BATTLE_BACKEND_GAME_CLIENT_H
#define SEA_BATTLE_BACKEND_GAME_CLIENT_H

#include <locale.h>
#include <cstddef>
#include <memory>
#include <string>
#include "sbcli/config/config.h"
#include "sbcli/controller/auth.h"
#include "sbcli/controller/game.h"
#include "sbcli/controller/menu.h"
#include "sbcli/core/test_client.h"

// TODO: добавить документацию к методам и свойствам

namespace seabattle {
namespace client {
namespace game {

namespace net = boost::asio;  // from <boost/asio.hpp>

class GameClient {
 public:
    GameClient(config::IpPort net_config, config::Debug debug);
    ~GameClient();
    size_t Run();

 private:
    size_t InitGraphics();

    std::unique_ptr<test::TestClient> test_client_;
    std::unique_ptr<controller::AuthController> auth_controller_;
    std::unique_ptr<controller::MenuController> menu_controller_;
    std::unique_ptr<controller::GameController> game_controller_;
    std::shared_ptr<network::TCPClient> network_client_;
    std::shared_ptr<config::ControllerSignal> controller_signal_;

    config::Debug debug_data_;
    config::IpPort net_config_;
};

}  // namespace game
}  // namespace client
}  // namespace seabattle

#endif  // SEA_BATTLE_BACKEND_GAME_CLIENT_H
