#include "game_client.h"
#include <iostream>

namespace seabattle {
namespace client {
namespace game {

GameClient::GameClient() : menu_controller_(new controller::MenuController()) {
    network_client_ = std::make_shared<network::TCPClient>(ioc);
    auth_controller_ = std::unique_ptr<controller::AuthController>(
        new controller::AuthController(network_client_));
}
size_t GameClient::run() {
    // TODO: возвращать значение команды без создания переменной в этой функции
    config::UserCommand user_command;
    // TODO: возвращать bool значение для статуса авторизированного пользователя без переменной
    utils::data::UserData user_data;
    while (true) {  // пока не выход
        auth_controller_->GetUserData(user_data);
        if (user_data.user_id == -1) {
            auth_controller_->Action(user_command);
        }
        switch (user_command.command){
            case config::EXIT_COMMAND:
                break;
            case config::MENU_COMMAND:
                menu_controller_->Action(user_command);
                break;
            case config::SINGLE_COMMAND:
                break;
            case config::LOAD_COMMAND:
                break;
            case config::MULTI_COMMAND:
                break;
        }

        if (user_command.command == config::EXIT_COMMAND) {
            break;
        }
    }
    std::cout << "Ура, мы вышли" << std::endl;

    // TODO: перенести в деструктор
    network_client_->Close();

    return 0;
}
}  // namespace game
}  // namespace client
}  // namespace seabattle
