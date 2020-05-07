#include "game_client.h"
#include <iostream>

namespace seabattle {
namespace client {
namespace game {

GameClient::GameClient()
    : network_client_(new network::NetworkClient()),
      menu_controller_(new controller::MenuController()) {
        auth_controller_ = std::unique_ptr<controller::AuthController>(new controller::AuthController(network_client_));

}
size_t GameClient::run() {
    config::UserCommand command;
    config::UserData user_data;
    while (command.command.compare("exit") != 0) {  // пока не выход
        auth_controller_->GetUserId(user_data);
        if (user_data.user_id == 0) {
            auth_controller_->Action(command);
        }
        if (command.command.compare("menu") == 0) {
            menu_controller_->Action(command);
        }
    }
    std::cout << "Ура, мы вышли" << std::endl;
    return 0;
}
}  // namespace game
}  // namespace client
}  // namespace seabattle
