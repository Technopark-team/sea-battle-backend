#include "user_model.h"

namespace seabattle {
namespace client {
namespace model {

UserModel::UserModel(std::shared_ptr<network::TCPClient>& network_client)
    : network_client_(network_client), user_data_(), auth_data_() {
    callback_ = std::make_shared<std::function<size_t(std::stringstream&)>>(
        std::bind(&UserModel::GeneralCallback_, this, std::placeholders::_1));
}

size_t UserModel::PostSignup() {
    user_data_.user_id = 1;  // тестовая инициализация
    return 0;
}

size_t UserModel::PostSignin() {
    utils::data::DataRequest req;
    req.route = utils::data::Routes::POST_SIGN_IN;
    req.auth_data = auth_data_;
    std::shared_ptr<std::stringstream> ss =
        seabattle::utils::serializer::Serializer<seabattle::utils::data::DataRequest>::Serialize(
            req);

    network_client_->Run(ss, callback_);
    return 0;
}

size_t UserModel::GetUserData(utils::data::UserData& user_data) {
    user_data = std::move(user_data_);
    return 0;
}

size_t UserModel::SetUserData(utils::data::UserData user_data) {
    user_data_ = std::move(user_data);
    std::cout << user_data_.user_id << std::endl;
    return 0;
}

size_t UserModel::GetAuthData(utils::data::AuthData& auth_data) {
    auth_data = std::move(auth_data_);
    return 0;
}

size_t UserModel::SetAuthData(utils::data::AuthData auth_data) {
    auth_data_ = std::move(auth_data);
    return 0;
}

size_t UserModel::GeneralCallback_(std::stringstream& response) {
    std::shared_ptr<utils::data::DataResponse> resp =
        utils::serializer::Serializer<utils::data::DataResponse>::Deserialize(
            response, response.str().size());

    switch (resp->route) {
        case utils::data::Routes::POST_SIGN_IN: {
            SetUserData(resp->user_data);
            break;
        }
        case utils::data::Routes::POST_SIGN_UP:
            break;
    }
    return 0; }

}  // namespace model
}  // namespace client
}  // namespace seabattle
