#include "game_client.h"
#include <iostream>
#include <memory>

namespace seabattle {
namespace client {
namespace game {

GameClient::GameClient(config::IpPort net_config, config::Debug debug)
    : net_config_(std::move(net_config)),
      debug_data_(std::move(debug)),
      menu_controller_(new controller::MenuController()) {
    std::cout << "[GameClient] GameClient" << std::endl;
    network_client_ = std::make_shared<network::TCPClient>(net_config_);
    test_client_ = std::make_unique<test::TestClient>(debug, network_client_);
    auth_controller_ = std::make_unique<controller::AuthController>(network_client_);
    game_controller_ = std::make_unique<controller::GameController>(network_client_);
    controller_signal_ = std::make_shared<config::ControllerSignal>(config::Controller::MENU);

    if (debug_data_.dev_mode == config::DevMode::RELEASE) {
        InitGraphics();
    }
}

GameClient::~GameClient() {
    std::cout << "[GameClient] ~GameClient" << std::endl;
//    network_client_->Close();
    if (debug_data_.dev_mode == config::DevMode::RELEASE) {
        endwin();
    }
}

size_t GameClient::InitGraphics() {
    std::cout << "[GameClient] InitGraphics" << std::endl;
    setlocale(LC_ALL, "");

    initscr();

    if (has_colors() == FALSE) {
        endwin();
        std::cout << "[GameClient] Your terminal does not support color\n" << std::endl;
        exit(1);
    }
    start_color();
}

size_t GameClient::Run() {
    std::cout << "[GameClient] Run" << std::endl;
    if (debug_data_.dev_mode == config::DevMode::DEV) {
        test_client_->Run();
    } else if (debug_data_.dev_mode == config::DevMode::RELEASE) {
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
    }
    std::cout << "[GameClient] Ура, мы вышли" << std::endl;

    return 0;
}
}  // namespace game
}  // namespace client
}  // namespace seabattle
