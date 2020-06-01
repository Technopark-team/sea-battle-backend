#include "game_client.h"
#include <iostream>
#include <memory>

namespace seabattle {
namespace client {
namespace game {

GameClient::GameClient(config::IpPort net_config, config::Debug debug) : menu_controller_(new controller::MenuController()) {
    network_client_ = std::make_shared<network::TCPClient>(ioc, net_config);
    auth_controller_ = std::make_unique<controller::AuthController>(network_client_);
    game_controller_ = std::make_unique<controller::GameController>(network_client_);
    controller_signal_ = std::make_shared<config::ControllerSignal>(config::Controller::MENU);
    controller_signal_->debug = std::move(debug);
    setlocale(LC_ALL, "");

    if (controller_signal_->debug.dev_mode == config::DevMode::RELEASE) {
        initscr();

        if(has_colors() == FALSE)
        {	endwin();
            printf("Your terminal does not support color\n");
            exit(1);
        }
        start_color();
    }

}

GameClient::~GameClient() {
    network_client_->Close();
    if (controller_signal_->debug.dev_mode == config::DevMode::RELEASE) {
        endwin();
    }
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
