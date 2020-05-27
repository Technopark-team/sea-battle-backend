#include "game_client.h"
#include <iostream>
#include <memory>

namespace seabattle {
namespace client {
namespace game {

GameClient::GameClient() : menu_controller_(new controller::MenuController()) {
    network_client_ = std::make_shared<network::TCPClient>(ioc);
    auth_controller_ = std::make_unique<controller::AuthController>(network_client_);
    game_controller_ = std::make_unique<controller::GameController>(network_client_);
    controller_signal_ = std::make_shared<config::ControllerSignal>(config::Controller::MENU);

    setlocale(LC_ALL, "");
    initscr();
}

GameClient::~GameClient() {
    network_client_->Close();
    endwin();
}

size_t GameClient::run() {
    while (controller_signal_->signal != config::Controller::NONE) {  // пока не закрытие
        switch (controller_signal_->signal) {
            case config::Controller::AUTH:
                auth_controller_->Action(controller_signal_);
                break;
            case config::Controller::MENU:
                menu_controller_->Action(controller_signal_);
                break;
            case config::Controller::GAME:
                game_controller_->Action(controller_signal_);
                break;
        }
    }
    std::cout << "Ура, мы вышли" << std::endl;

    return 0;
}
}  // namespace game
}  // namespace client
}  // namespace seabattle
