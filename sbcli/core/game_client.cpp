#include "game_client.h"
#include <iostream>

namespace seabattle {
namespace client {
namespace game {

GameClient::GameClient()
    : menu_controller_(new controller::MenuController()) {
    network_client_ = std::make_shared<network::TCPClient>(ioc);
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
    network_client_->Close();

    return 0;
}
}  // namespace game
}  // namespace client
}  // namespace seabattle
