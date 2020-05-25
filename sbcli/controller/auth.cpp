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
    size_t auth_status = controller_signal->auth_user_status;
    controller_signal->Clean();
    utils::data::TestAuthData auth_data;

    console_interface_->Run(command, auth_data, auth_status);

    if (controller_signal->auth_user_status == config::UserStatus::AUTHORIZED) {
        if (command == 0) {
            // TODO: сделать logout в модели и на сервере
        }
    } else {
        if (command == 0) {
            // TODO: провалидировать auth_data
            user_model_->SetAuthData(auth_data);

            // TODO: вызвать PostSignin()/PostSignup() в зависимости от команды авторизации или
            // регистрации
            // TODO: это неблокирующая операция, требуется синхронизировать асинхронную операцию
            user_model_->CreateUser();
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            GetUserData(controller_signal->user_id);
            controller_signal->auth_user_status = config::UserStatus::AUTHORIZED;
        }
    }
    controller_signal->signal = config::Controller::MENU;
    return 0;
}

size_t AuthController::GetUserData(int &user_id) {
    user_model_->GetUserData(user_id);
    return 0;
}

}  // namespace controller
}  // namespace client
}  // namespace seabattle