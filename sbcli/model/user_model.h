#ifndef SEA_BATTLE_BACKEND_USER_MODEL_H
#define SEA_BATTLE_BACKEND_USER_MODEL_H

#include <memory>
#include "../sbcli/config/config.h"
#include "model_inteface.h"
#include "network/network.h"
#include "sbutils/data/data.h"

namespace seabattle {
namespace client {
namespace model {

// TODO: добавить документацию к методам и свойствам

class UserModel : public IModel {
 public:
    explicit UserModel(std::shared_ptr<network::TCPClient> &network_client);
    ~UserModel() = default;

    size_t PostSignup() override;
    size_t PostSignin() override;
    size_t GetUserId(config::UserData &user_data);
    size_t SetUserId(config::UserData user_data);
    size_t GetAuthData(utils::data::AuthData &auth_data);
    size_t SetAuthData(utils::data::AuthData auth_data);

 private:
    size_t GeneralCallback_(std::string response) override;

    config::UserData user_data_;
    utils::data::AuthData auth_data_;
    std::shared_ptr<network::TCPClient> network_client_;

};

}
}
}


#endif //SEA_BATTLE_BACKEND_USER_MODEL_H
