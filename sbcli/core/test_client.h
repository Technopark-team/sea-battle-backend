#ifndef SEABATTLE_SBCLI_CORE_TEST_CLIENT_H_
#define SEABATTLE_SBCLI_CORE_TEST_CLIENT_H_

#include <memory>
#include <chrono>
#include <thread>
#include "network/network.h"
#include "sbcli/config/config.h"
#include "sbutils/serialization/serializer.h"

namespace seabattle {
namespace client {
namespace test {

class TestClient {
 public:
    explicit TestClient(config::Debug debug_data,
                        std::shared_ptr<network::TCPClient>& network_client);
    ~TestClient() = default;

    size_t Run();

 private:
    size_t TestCreateSession_();
    size_t TestUpdateGame_();
    size_t TestJoinSession_();
    size_t TestStartGame_();
    size_t TestCreateUser_();
    size_t TestEnter_();
    size_t TestEndGame_();
    size_t GeneralCallback_(std::stringstream& response);

    int user1_id_;
    int user2_id_;
    int user1_session_id_;
    int user2_session_id_;
    std::shared_ptr<network::TCPClient> network_client_;
    std::shared_ptr<std::function<size_t(std::stringstream&)>> callback_;

    config::Debug debug_data_;
};

}  // namespace test
}  // namespace client
}  // namespace seabattle

#endif  // SEABATTLE_SBCLI_CORE_TEST_CLIENT_H_
