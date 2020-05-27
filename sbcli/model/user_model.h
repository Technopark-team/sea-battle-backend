#ifndef SEA_BATTLE_BACKEND_USER_MODEL_H
#define SEA_BATTLE_BACKEND_USER_MODEL_H

#include <memory>
#include "sbcli/config/config.h"
#include "sbutils/serialization/serializer.h"
#include "model_inteface.h"
#include "network/network.h"

namespace seabattle {
namespace client {
namespace model {

// TODO: добавить документацию к методам и свойствам
// TODO: добавить сохранение данных пользователя в файл ака Cookies для автоматической авторизации. Потом в конструкторе можно сразу инициализировать UserData.

class UserModel : public IModel {
 public:
    explicit UserModel(std::shared_ptr<network::TCPClient> &network_client);
    ~UserModel() = default;

    size_t CreateUser() override;
    size_t Enter() override;
    size_t GetUserData(int &user_id);
    size_t SetUserData(int user_id);
    size_t GetAuthData(utils::data::TestAuthData &auth_data);
    size_t SetAuthData(utils::data::TestAuthData auth_data);

 private:
    size_t GeneralCallback_(std::stringstream& response) override;

    int user_id_;
    utils::data::TestAuthData auth_data_;
    std::shared_ptr<network::TCPClient> network_client_;
    std::shared_ptr<std::function<size_t(std::stringstream&)>> callback_;
};

}  // namespace model
}  // namespace client
}  // namespace seabattle

#endif  // SEA_BATTLE_BACKEND_USER_MODEL_H
