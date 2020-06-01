#include "auth.h"

#include <chrono>
#include <thread>

namespace seabattle {
namespace client {
namespace controller {

AuthController::AuthController(std::shared_ptr<network::TCPClient>& network_client)
    : user_model_(new model::UserModel(network_client)),
      console_interface_(new view::AuthConsoleInput()) {}

size_t AuthController::Action(std::shared_ptr<config::ControllerSignal>& controller_signal) {
    size_t command = -1;
    config::UserStatus auth_status = controller_signal->auth_user_status;
    config::UserCommand menu_command = controller_signal->command;
    controller_signal->Clean();
    utils::data::TestAuthData auth_data;

    // TODO: для отаадки закоммннтировать и руками заиить знаееняя auth_data
    if (controller_signal->debug.dev_mode == config::DevMode::RELEASE) {
        console_interface_->Run(command, auth_data, auth_status);
    } else {
        auth_data = std::move(controller_signal->debug.auth_data);
//        controller_signal->auth_user_status = config::UserStatus::AUTHORIZED;
        command = 0;
        menu_command.command = config::UserCommandId::SIGNIN_COMMAND;
    }
//    auth_data.login_ = "123";
//    auth_data.password_ = "123";

    // TODO: переписать эти условные конструкции
    if (controller_signal->auth_user_status == config::UserStatus::AUTHORIZED) {
        if (command == 0) {
//            GetUserData(controller_signal->user_id);
//            user_model_->Enter();
            // TODO: сделать logout в модели и на сервере
        }
    } else {
        if (command == 0) {
            // TODO: провалидировать auth_data
            user_model_->SetAuthData(auth_data);

            // TODO: вызвать PostSignin()/PostSignup() в зависимости от команды авторизации или регистрации
            // TODO: это неблокирующая операция, требуется синхронизировать асинхронную операцию
            switch (menu_command.command) {
                case config::UserCommandId::SIGNIN_COMMAND:
                    user_model_->Enter();
                    break;
                case config::UserCommandId::SIGNUP_COMMAND:
                    user_model_->CreateUser();
                    break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            GetUserData(controller_signal->user_id);
            controller_signal->auth_user_status = config::UserStatus::AUTHORIZED;
        }
    }
    // command == 1 - возвращение в меню
    // TODO: для отаадки просааиить game
    controller_signal->signal = config::Controller::MENU;
    return 0;
}

size_t AuthController::GetUserData(int& user_id) {
    user_model_->GetUserData(user_id);
    std::cout << user_id << std::endl;
    return 0;
}

}  // namespace controller
}  // namespace client
}  // namespace seabattle