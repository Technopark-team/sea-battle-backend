#include "user_model.h"

namespace seabattle {
namespace client {
namespace model {

// TODO: внутри каждой функции Set... должен быть интегрирован валидатор

UserModel::UserModel(std::shared_ptr<network::TCPClient>& network_client)
    : network_client_(network_client), user_id_(), auth_data_() {
    callback_ = std::make_shared<std::function<size_t(std::stringstream&)>>(
        std::bind(&UserModel::GeneralCallback_, this, std::placeholders::_1));
}

size_t UserModel::CreateUser() {
    utils::data::TestDataRequest req;
    req.type_ = utils::data::TestRoute::CreateUser;
    req.data_ = auth_data_;
    std::shared_ptr<std::stringstream> ss = seabattle::utils::serializer::Serializer<
        seabattle::utils::data::TestDataRequest>::Serialize(req);

    network_client_->Run(ss, callback_);
    return 0;
}

size_t UserModel::Enter() {
    utils::data::TestDataRequest req;
    req.type_ = utils::data::TestRoute::Enter;
    req.data_ = auth_data_;
    std::shared_ptr<std::stringstream> ss = seabattle::utils::serializer::Serializer<
        seabattle::utils::data::TestDataRequest>::Serialize(req);

    network_client_->Run(ss, callback_);
    return 0;
}

size_t UserModel::GetUserData(int& user_id) {
    user_id = user_id_;
    return 0;
}

size_t UserModel::SetUserData(int user_id) {
    user_id_ = user_id;
    std::cout << user_id_ << std::endl;
    return 0;
}

size_t UserModel::GetAuthData(utils::data::TestAuthData& auth_data) {
    auth_data = std::move(auth_data_);
    return 0;
}

size_t UserModel::SetAuthData(utils::data::TestAuthData auth_data) {
    auth_data_ = std::move(auth_data);
    return 0;
}

size_t UserModel::GeneralCallback_(std::stringstream& response) {
    std::shared_ptr<utils::data::TestDataResponse> resp =
        utils::serializer::Serializer<utils::data::TestDataResponse>::Deserialize(
            response, response.str().size());

    SetUserData(resp->user_id_);
    return 0;
}

}  // namespace model
}  // namespace client
}  // namespace seabattle
