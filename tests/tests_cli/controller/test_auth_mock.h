#ifndef SEABATTLE_TESTS_TESTS_CLI_CONTROLLER_TEST_AUTH_MOCK_H_
#define SEABATTLE_TESTS_TESTS_CLI_CONTROLLER_TEST_AUTH_MOCK_H_

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../../../sbcli/controller/auth.h"
#include "../../../sbcli/network/network.h"
#include "../../../sbcli/config/config.h"

namespace seabattle {
namespace client {
namespace test {

namespace net = boost::asio;            // from <boost/asio.hpp>

struct UserData {
    int user_id = 0;
};
struct UserCommand {
    std::string command{};
};

class MockUserCommand : public config::UserCommand {
 public:
    MockUserCommand() : UserCommand(){};
};

class MockAuthController : public controller::AuthController {
 public:
    MockAuthController(std::shared_ptr<network::TCPClient> &network_client_) : AuthController(network_client_){};
//    MOCK_METHOD1(Action, size_t(config::UserCommand&));
    MOCK_METHOD1(Action, size_t(UserCommand&));
    MOCK_METHOD1(GetUserId, size_t(config::UserData&));
};

TEST(MockAuthController, Action_GetUserId) {
    net::io_context ioc;
    std::shared_ptr<network::TCPClient> network_client_ = std::make_shared<network::TCPClient>(ioc);

    MockAuthController ser(network_client_);

    config::UserData user_data;
//    config::UserCommand user_command;
    UserCommand user_command;

    EXPECT_CALL(ser, Action(user_command)).Times(1);
//    EXPECT_EQ(ser.Action(user_command), 0);
    EXPECT_CALL(ser, GetUserId(user_data)).Times(1);
//    EXPECT_EQ(ser.GetUserId(user_data), 0);
}

}  // namespace test
}  // namespace client
}  // namespace seabattle

#endif  // SEABATTLE_TESTS_TESTS_CLI_CONTROLLER_TEST_AUTH_MOCK1_H_
