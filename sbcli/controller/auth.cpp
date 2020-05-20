#include "auth.h"

#include <chrono>
#include <thread>

namespace seabattle {
namespace client {
namespace controller {

AuthController::AuthController(std::shared_ptr<network::TCPClient>& network_client)
    : user_model_(new model::UserModel(network_client)),
      console_interface_(new ui::AuthConsoleInput()) {}

size_t AuthController::Action(std::shared_ptr<config::ControllerSignal>& controller_signal) {
    size_t auth_status = controller_signal->auth_user_status;
    controller_signal->Clean();
    size_t command;
    utils::data::AuthData auth_data;
    if (controller_signal->auth_user_status == config::UserStatus::AUTHORIZED) {
        console_interface_->RenderAuth(command);
        if (command == 0) {
            // TODO: сделать logout в модели и на сервере
        }
    } else {
        console_interface_->RenderNonAuth(command);
        if (command == 0) {
            console_interface_->ReadAuthData(auth_data);
            // TODO: провалидировать auth_data
            user_model_->SetAuthData(auth_data);

            // TODO: вызвать PostSignin()/PostSignup() в зависимости от команды авторизации или
            // регистрации
            // TODO: это неблокирующая операция, требуется синхронизировать асинхронную операцию
            user_model_->PostSignin();
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            GetUserData(controller_signal->user_data);
            controller_signal->auth_user_status = config::UserStatus::AUTHORIZED;
        }
    }
    controller_signal->signal = config::Controller::MENU;
    //    config::UserCommand auth_command;
    //    utils::data::AuthData auth_data;
    //
    //    console_interface_->ReadCommand(auth_command);
    //
    //    // TODO: проверить, что введена команда авторизации или регистрации
    //    console_interface_->ReadAuthData(auth_data);
    //

    //
    //    // TODO: продумать view, которая рендерит успех/неудачу авторизации/регистрации
    //    // TODO: предложение пользователю войти в меню или выйти из игры только после успеха
    //    // TODO: вынести из контроллера авторизации, так как не его поле деятельности
    ////    console_interface_->ReadCommand(user_command);
    //    controller_signal->signal = config::Controller::NONE;
    return 0;
}

size_t AuthController::GetUserData(utils::data::UserData& user_data) {
    user_model_->GetUserData(user_data);
    return 0;
}

}  // namespace controller
}  // namespace client
}  // namespace seabattle