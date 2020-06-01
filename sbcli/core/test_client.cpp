#include "test_client.h"

namespace seabattle {
namespace client {
namespace test {

TestClient::TestClient(config::Debug debug_data,
                       std::shared_ptr<network::TCPClient>& network_client)
    : debug_data_(std::move(debug_data)), network_client_(network_client) {
    std::cout << "[TestClient] TestClient" << std::endl;

    callback_ = std::make_shared<std::function<size_t(std::stringstream&)>>(
        std::bind(&TestClient::GeneralCallback_, this, std::placeholders::_1));
}

size_t TestClient::Run() {
    std::cout << "[TestClient] Run" << std::endl;

    TestCreateUser_();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    return 0;
}

size_t TestClient::TestCreateUser_() {
    std::cout << "[TestClient] TestCreateUser_" << std::endl;

    utils::data::TestDataRequest req;
    req.type_ = utils::data::TestRoute::CreateUser;
    req.data_ = std::move(debug_data_.auth_data);
    std::shared_ptr<std::stringstream> ss = seabattle::utils::serializer::Serializer<
        seabattle::utils::data::TestDataRequest>::Serialize(req);

    network_client_->Run(ss, callback_);
    return 0;
}

size_t TestClient::TestEnter_() {
    std::cout << "[TestClient] TestEnter_" << std::endl;

    utils::data::TestDataRequest req;
    req.type_ = utils::data::TestRoute::Enter;
    req.data_ = std::move(debug_data_.auth_data);
    std::shared_ptr<std::stringstream> ss = seabattle::utils::serializer::Serializer<
        seabattle::utils::data::TestDataRequest>::Serialize(req);

    network_client_->Run(ss, callback_);
    return 0;
}

size_t TestClient::TestCreateSession_() {
    std::cout << "[TestClient] TestCreateSession_" << std::endl;
    return 0;
}

size_t TestClient::TestJoinSession_() {
    std::cout << "[TestClient] TestJoinSession_" << std::endl;
    return 0;
}

size_t TestClient::TestStartGame_() {
    std::cout << "[TestClient] TestStartGame_" << std::endl;
    return 0;
}

size_t TestClient::GeneralCallback_(std::stringstream& response) {
    std::cout << "[TestClient] GeneralCallback_" << std::endl;

    std::shared_ptr<utils::data::TestDataResponse> resp =
        utils::serializer::Serializer<utils::data::TestDataResponse>::Deserialize(
            response, response.str().size());
    switch (resp->type_) {
        case utils::data::TestRoute::CreateUser: {
            std::cout << "[SERVER RESPONSE] CreateUser with id \"" << resp->user_id_ << "\""
                      << std::endl;
            user1_id_ = resp->user_id_;
            break;
        }
        case utils::data::TestRoute::Enter: {
            std::cout << "[SERVER RESPONSE] Enter with id \"" << resp->user_id_ << "\""
                      << std::endl;
            user2_id_ = resp->user_id_;
            break;
        }
        case utils::data::TestRoute::CreateSession: {
            std::cout << "[SERVER RESPONSE] CreateSession" << std::endl;
            user1_session_id_ = resp->session_id_;
            break;
        }
        case utils::data::TestRoute::StartGame: {
            std::cout << "[SERVER RESPONSE] StartGame" << std::endl;

            break;
        }
        case utils::data::TestRoute::UpdateGame: {
            std::cout << "[SERVER RESPONSE] UpdateGame" << std::endl;

            break;
        }
        case utils::data::TestRoute::JoinSession: {
            std::cout << "[SERVER RESPONSE] JoinSession" << std::endl;
            user2_session_id_ = resp->session_id_;
            break;
        }
        case utils::data::TestRoute::EndGame: {
            std::cout << "[SERVER RESPONSE] EndGame" << std::endl;
            break;
        }
    }
    return 0;
}

}  // namespace test
}  // namespace client
}