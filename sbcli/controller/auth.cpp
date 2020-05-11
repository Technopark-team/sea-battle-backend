#include "auth.h"

namespace seabattle {
namespace client {
namespace controller {

AuthController::AuthController(std::shared_ptr<network::TCPClient>& network_client)
    : user_model_(new model::UserModel(network_client)),
      console_interface_(new ui::AuthConsoleInput()) {}

size_t AuthController::Action(config::UserCommand& user_command) {
    config::UserCommand auth_command;
    utils::data::AuthData auth_data;

    console_interface_->ReadCommand(auth_command);

    // TODO: проверить, что введена команда авторизации или регистрации
    console_interface_->ReadAuthData(auth_data);

    // TODO: сохранить auth_data в модель
    // TODO: вызвать PostSignin()/PostSignup() в зависимости от команды авторизации или регистрации
    // TODO: это блокирующая операция, требуется продумать корректный коллбек
    user_model_->PostSignin();

    // TODO: продумать view, которая рендерит успех/неудачу авторизации/регистрации
    // TODO: предложение пользователю войти в меню или выйти из игры только после успеха
    console_interface_->ReadCommand(user_command);
    return 0;
}

size_t AuthController::GetUserId(config::UserData& user_data) {
    user_model_->GetUserId(user_data);
    return 0;
}

}  // namespace controller
}  // namespace client
}  // namespace seabattle