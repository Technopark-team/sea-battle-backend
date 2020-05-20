#ifndef SEA_BATTLE_BACKEND_AUTH_H
#define SEA_BATTLE_BACKEND_AUTH_H

#include <memory>
#include <locale.h>
#include "controller_interface.h"
#include "sbcli/config/config.h"
#include "sbcli/model/user_model.h"
#include "sbutils/data/data.h"
#include "view/auth_console_input.h"

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
     * This method takes signal for using controller in next step, auth_user_status for defining
     * whether user has authorized, user_id to define user, command to define command for controllers
     * @param controller_signal
     * @return
     */
    size_t Action(std::shared_ptr<config::ControllerSignal> &controller_signal) override;

    /**
     * This method provides access to user model to get its ID after success auth/reg.
     * @param user_data
     * @return
     */
    size_t GetUserData(utils::data::UserData &user_data);

 private:
    /**
     * This prop is smart pointer to model::UserModel obj.
     */
    std::unique_ptr<model::UserModel> user_model_;

    /**
     * This prop is smart pointer to view::AuthConsoleInput.
     */
    std::unique_ptr<view::AuthConsoleInput> console_interface_;
};

}  // namespace controller
}  // namespace client
}  // namespace seabattle

#endif  // SEA_BATTLE_BACKEND_AUTH_H
