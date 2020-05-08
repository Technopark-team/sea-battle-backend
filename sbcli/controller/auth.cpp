#include "auth.h"

namespace seabattle {
namespace client {
namespace controller {

AuthController::AuthController(
    std::shared_ptr<network::TCPClient> &network_client)
    : user_model_(new model::UserModel(network_client)),
      console_interface_(new ui::AuthConsoleInput()) {}

size_t AuthController::Action(config::UserCommand& user_command) {
    config::UserCommand auth_command;
    console_interface_->ReadCommand(auth_command);
    // TODO: проверить, что введена команда авторизации или регистрации
    config::AuthData auth_data;
    console_interface_->ReadAuthData(auth_data);
    user_model_->PostSignin();
    // TODO: продумать view, которая рендерит успех/неудачу авторизации/регистрации
    console_interface_->ReadCommand(
        user_command);  // предложение пользователю выйти в меню или выйти из игры
    return 0;
}

size_t AuthController::GetUserId(config::UserData& user_data) {
    user_model_->GetUserId(user_data);
    return 0;
}

}  // namespace controller
}  // namespace client
}  // namespace seabattle