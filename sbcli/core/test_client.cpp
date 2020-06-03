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

size_t TestClient::EmulateCreateClient() {
    std::cout << "[TestClient] Run" << std::endl;

    TestCreateUser_();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    TestCreateSession_();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    int wait1;
    std::cout << "wait to StartGame ";
    std::cin >> wait1;

    TestStartGame_();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    int wait2;
    std::cout << "wait to UpdateGame ";
    std::cin >> wait2;

    TestUpdateGame_();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    int wait3;
    std::cout << "wait to UpdateGame";
    std::cin >> wait3;

    while (!game_state_.end_game_) {
        while (game_state_.next_step_id_ != user_id_) {
            TestUpdateGame_();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}

size_t TestClient::EmulateJoinClient() {
    std::cout << "[TestClient] Run" << std::endl;

    TestCreateUser_();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    TestJoinSession_();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    int wait1;
    std::cout << "wait to StartGame";
    std::cin >> wait1;

    TestStartGame_();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    int wait2;
    std::cout << "wait to UpdateGame ";
    std::cin >> wait2;

    TestUpdateGame_();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    int wait3;
    std::cout << "wait to UpdateGame";
    std::cin >> wait3;

    while (!game_state_.end_game_) {
        while (game_state_.next_step_id_ != user_id_) {
            TestUpdateGame_();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}

size_t TestClient::Run() {
    if (debug_data_.user_n == config::User_n::USER1) {
        EmulateCreateClient();
    } else {
        EmulateJoinClient();
    }

    return 0;
}

size_t TestClient::TestCreateUser_() {
    std::cout << "[TestClient] TestCreateUser_" << std::endl;

    utils::data::TestDataRequest req;
    req.type_ = utils::data::TestRoute::CreateUser;
    req.data_ = std::move(debug_data_.auth_data);
    std::shared_ptr<std::stringstream> ss = seabattle::utils::serializer::Serializer<
        seabattle::utils::data::TestDataRequest>::Serialize(req);

    network_client_->Run(ss, callback_, 1);
    return 0;
}

size_t TestClient::TestEnter_() {
    std::cout << "[TestClient] TestEnter_" << std::endl;

    utils::data::TestDataRequest req;
    req.type_ = utils::data::TestRoute::Enter;
    req.data_ = std::move(debug_data_.auth_data);
    std::shared_ptr<std::stringstream> ss = seabattle::utils::serializer::Serializer<
        seabattle::utils::data::TestDataRequest>::Serialize(req);

    network_client_->Run(ss, callback_, 1);
    return 0;
}

size_t TestClient::TestCreateSession_() {
    std::cout << "[TestClient] TestCreateSession_" << std::endl;

    utils::data::TestDataRequest req;
    req.type_ = utils::data::TestRoute::CreateSession;
    req.user_id_ = std::move(user_id_);
    std::shared_ptr<std::stringstream> ss = seabattle::utils::serializer::Serializer<
        seabattle::utils::data::TestDataRequest>::Serialize(req);

    network_client_->Run(ss, callback_, 1);

    return 0;
}

size_t TestClient::TestJoinSession_() {
    std::cout << "[TestClient] TestJoinSession_" << std::endl;

    utils::data::TestDataRequest req;
    req.type_ = utils::data::TestRoute::JoinSession;
    req.user_id_ = std::move(user_id_);
    req.session_id_ = debug_data_.join_session_id;  // задавать руками
    std::shared_ptr<std::stringstream> ss = seabattle::utils::serializer::Serializer<
        seabattle::utils::data::TestDataRequest>::Serialize(req);

    network_client_->Run(ss, callback_, 2);
    return 0;
}

size_t TestClient::TestStartGame_() {
    std::cout << "[TestClient] TestStartGame_" << std::endl;

    utils::data::TestDataRequest req;
    req.type_ = utils::data::TestRoute::StartGame;
    req.session_id_ = session_id_;
    req.user_id_ = user_id_;
    req.map_ = std::move(debug_data_.debug_map);

    std::shared_ptr<std::stringstream> ss = seabattle::utils::serializer::Serializer<
        seabattle::utils::data::TestDataRequest>::Serialize(req);

    network_client_->Run(ss, callback_, 2);

    return 0;
}

size_t TestClient::TestUpdateGame_() {
    std::cout << "[TestClient] TestUpdateGame_" << std::endl;

    utils::data::TestDataRequest req;
    req.type_ = utils::data::TestRoute::UpdateGame;
    req.session_id_ = session_id_;
    req.user_id_ = user_id_;

    std::cout << "input x, y: ";
    std::cin >> req.point_.x_ >> req.point_.y_;

    std::shared_ptr<std::stringstream> ss = seabattle::utils::serializer::Serializer<
        seabattle::utils::data::TestDataRequest>::Serialize(req);

    network_client_->Run(ss, callback_, 2);

    return 0;
}

size_t TestClient::TestEndGame_() {
    std::cout << "[TestClient] TestEndGame_" << std::endl;

    utils::data::TestDataRequest req;
    req.type_ = utils::data::TestRoute::EndGame;

    std::shared_ptr<std::stringstream> ss = seabattle::utils::serializer::Serializer<
        seabattle::utils::data::TestDataRequest>::Serialize(req);

    network_client_->Run(ss, callback_, 1);
    return 0;
}

size_t TestClient::GeneralCallback_(std::stringstream& response) {
    std::cout << "============================" <<  std::endl;
    std::cout << "[TestClient] GeneralCallback_" << std::endl;

    std::shared_ptr<utils::data::TestDataResponse> resp =
        utils::serializer::Serializer<utils::data::TestDataResponse>::Deserialize(
            response, response.str().size());
    switch (resp->type_) {
        case utils::data::TestRoute::CreateUser: {
            std::cout << "[SERVER RESPONSE] CreateUser with id \"" << resp->user_id_ << "\""
                      << std::endl;
            user_id_ = resp->user_id_;
            break;
        }
        case utils::data::TestRoute::Enter: {
            std::cout << "[SERVER RESPONSE] Enter with id \"" << resp->user_id_ << "\""
                      << std::endl;
            user2_id_ = resp->user_id_;
            break;
        }
        case utils::data::TestRoute::CreateSession: {
            std::cout << "[SERVER RESPONSE] CreateSession with id \"" << resp->session_id_ << "\""
                      << std::endl;
            std::cout << "[SERVER RESPONSE] user_id_ " << resp->user_id_ << std::endl;

            user1_session_id_ = resp->session_id_;
            break;
        }
        case utils::data::TestRoute::StartGame: {
            std::cout << "[SERVER RESPONSE] StartGame" << std::endl;

            std::cout << "[SERVER RESPONSE] user_id_ " << resp->user_id_ << std::endl;
            std::cout << "[SERVER RESPONSE] resp->session_id_ " << resp->session_id_ << std::endl;
            std::cout << "[SERVER RESPONSE] resp->error_ " << static_cast<int>(resp->error_)
                      << std::endl;
            std::cout << "[SERVER RESPONSE] resp->game_state_.next_step_id_ "
                      << resp->game_state_.next_step_id_ << std::endl;
            std::cout << "[SERVER RESPONSE] resp->game_state_.result "
                      << static_cast<int>(resp->game_state_.result_) << std::endl;
            std::cout << "[SERVER RESPONSE] resp->game_state_.end_game_ "
                      << static_cast<int>(resp->game_state_.end_game_) << std::endl;
            game_state_ = std::move(resp->game_state_);
            enemy_point_ = std::move(resp->point_);


            break;
        }
        case utils::data::TestRoute::UpdateGame: {
            std::cout << "[SERVER RESPONSE] UpdateGame" << std::endl;
            std::cout << "[SERVER RESPONSE] user_id_ " << resp->user_id_ << std::endl;

            std::cout << "[SERVER RESPONSE] resp->game_state_.result_ "
                      << static_cast<int>(resp->game_state_.result_) << std::endl;
            std::cout << "[SERVER RESPONSE] resp->point_ " << resp->point_.x_ << resp->point_.y_
                      << std::endl;

            std::cout << "[SERVER RESPONSE] resp->session_id_ " << resp->session_id_ << std::endl;
            std::cout << "[SERVER RESPONSE] resp->error_ " << static_cast<int>(resp->error_)
                      << std::endl;
            std::cout << "[SERVER RESPONSE] resp->game_state_.next_step_id_ "
                      << resp->game_state_.next_step_id_ << std::endl;
            std::cout << "[SERVER RESPONSE] resp->game_state_.result "
                      << static_cast<int>(resp->game_state_.result_) << std::endl;
            std::cout << "[SERVER RESPONSE] resp->game_state_.end_game_ "
                      << static_cast<int>(resp->game_state_.end_game_) << std::endl;
            game_state_ = std::move(resp->game_state_);
            enemy_point_ = std::move(resp->point_);

            break;
        }
        case utils::data::TestRoute::JoinSession: {
            std::cout << "[SERVER RESPONSE] JoinSession with id \"" << session_id_ << "\""
                      << std::endl;
            std::cout << "[SERVER RESPONSE] user_id: " << user_id_ << std::endl;
            std::cout << "[SERVER RESPONSE] resp->error_ " << static_cast<int>(resp->error_)
                      << std::endl;
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
}  // namespace seabattle