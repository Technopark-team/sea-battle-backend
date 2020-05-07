#ifndef SEA_BATTLE_BACKEND_AUTH_H
#define SEA_BATTLE_BACKEND_AUTH_H

#include <memory>
#include "../sbcli/config/config.h"
#include "../sbcli/model/user_model.h"
#include "controller_interface.h"
#include "ui/auth_console_input.h"

namespace seabattle {
namespace client {
namespace controller {

/**
 * Controller for authorization/registration
 */
class AuthController : public IController {
 public:
    explicit AuthController(
        std::shared_ptr<seabattle::client::network::INetworkClient> &network_client);
    ~AuthController() = default;

    /**
     * This method for AuthController
     * @param user_command
     * @param network_client
     * @return
     */
    size_t Action(config::UserCommand &user_command) override;
    size_t GetUserId(config::UserData &user_data);

 private:
    std::unique_ptr<model::UserModel> user_model_;
    std::unique_ptr<ui::AuthConsoleInput> console_interface_;
};

}  // namespace controller
}  // namespace client
}  // namespace seabattle

#endif  // SEA_BATTLE_BACKEND_AUTH_H
