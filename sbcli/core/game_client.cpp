#include "game_client.h"
#include <iostream>
#include <memory>

namespace seabattle {
namespace client {
namespace game {

GameClient::GameClient() : menu_controller_(new controller::MenuController()) {
    network_client_ = std::make_shared<network::TCPClient>(ioc);
    auth_controller_ = std::make_unique<controller::AuthController>(network_client_);
}
size_t GameClient::run() {
    /* TODO: возвращать значение команды без создания переменной в этой функции
     * Требуется определиться с логикой контроллеров:
     *
     * Может быть, создать сигналы переходов между контроллерами (сигнал соответсвует контроллеру)
     * а также статус пользователя:
     *      enum ControllerSignal {
     *          MENU = 1,
     *          AUTH,
     *          GAME,
     *      }
     *      enum UserStatus {
     *          EXIST = 1,
     *          NONEXIST,
     *      }
     *      size_t user_status_ = 0;
     */
    config::UserCommand user_command;
    // TODO: возвращать bool значение для статуса авторизированного пользователя без переменной (outdated: нам нужны данные по пользователю для игровой модели)
    utils::data::UserData user_data;
    while (user_command.command != config::CLOSE_COMMAND) {  // пока не закрытие
        auth_controller_->GetUserData(user_data);
        if (user_data.user_id == -1) {
            auth_controller_->Action(user_command);
        }
        switch (user_command.command){
            case config::CLOSE_COMMAND:
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

        if (user_command.command == config::CLOSE_COMMAND) {
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
