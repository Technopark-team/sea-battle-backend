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
 * Controller for user authorization/registration
 */
class AuthController : public IController {
 public:
    explicit AuthController(std::shared_ptr<network::TCPClient> &network_client);
    ~AuthController() = default;

    /**
     * This method takes user's cmd for auth/reg, next takes log/pass and calls model for async net
     * communication with server to fill UserData struct. The last step is to take user's cmd for
     * menu/exit as callback after success auth/reg.
     * @param user_command stores menu/exit req from user
     * @return
     */
    size_t Action(config::UserCommand &user_command) override;

    /**
     * This method provides access to user model to get its ID after success auth/reg.
     * @param user_data
     * @return
     */
    size_t GetUserId(config::UserData &user_data);

 private:
    /**
     * This prop is smart pointer to model::UserModel obj.
     */
    std::unique_ptr<model::UserModel> user_model_;

    /**
     * This prop is smart pointer to ui::AuthConsoleInput.
     */
    std::unique_ptr<ui::AuthConsoleInput> console_interface_;
};

}  // namespace controller
}  // namespace client
}  // namespace seabattle

#endif  // SEA_BATTLE_BACKEND_AUTH_H
