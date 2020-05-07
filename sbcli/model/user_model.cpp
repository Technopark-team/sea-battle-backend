#include "user_model.h"

namespace seabattle {
namespace client {
namespace model {

UserModel::UserModel(std::shared_ptr<seabattle::client::network::INetworkClient> network_client)
    : network_client_(network_client), user_data_(), auth_data_() {}

size_t UserModel::PostSignup() {
    user_data_.user_id = 1;  // тестовая инициализация
    return 0;
}

size_t UserModel::PostSignin() {
    user_data_.user_id = 1;  // тестовая инициализация
    return 0;
}

size_t UserModel::GetUserId(config::UserData& user_data) {
    user_data = std::move(user_data_);
    return 0;
}

size_t UserModel::SetUserId(config::UserData user_data) {
    user_data_ = std::move(user_data);
    return 0;
}

size_t UserModel::GetAuthData(config::AuthData& auth_data) {
    auth_data = std::move(auth_data_);
    return 0;
}

size_t UserModel::SetAuthData(config::AuthData auth_data) {
    auth_data_ = std::move(auth_data);
    return 0;
}

size_t UserModel::GeneralCallback_(std::string response) { return 0; }

}  // namespace model
}  // namespace client
}  // namespace seabattle
