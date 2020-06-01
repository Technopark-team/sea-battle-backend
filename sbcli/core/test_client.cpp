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

    if (debug_data_.user_n == config::User_n::USER1) {
        TestCreateSession_();
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    } else {
        TestJoinSession_();
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    TestStartGame_();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    int wait;
    std::cout << "wait ";
    std::cin >> wait;

    TestUpdateGame_();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    utils::data::TestPoint enemy_point;
    utils::data::TestGameState game_state;

    while (!debug_data_.game_state.end_game_) {
        while (debug_data_.game_state.next_step_id_ != debug_data_.user_id) {
            enemy_point = std::move(debug_data_.enemy_point);
            game_state = std::move(debug_data_.game_state);
        }
        TestUpdateGame_();

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
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

    utils::data::TestDataRequest req;
    req.type_ = utils::data::TestRoute::CreateSession;
    req.user_id_ = std::move(user1_id_);
    req.user_id_ = std::move(user1_id_);
    debug_data_.user_id = user1_id_;
    std::shared_ptr<std::stringstream> ss = seabattle::utils::serializer::Serializer<
        seabattle::utils::data::TestDataRequest>::Serialize(req);

    network_client_->Run(ss, callback_);

    return 0;
}

size_t TestClient::TestJoinSession_() {
    std::cout << "[TestClient] TestJoinSession_" << std::endl;

    utils::data::TestDataRequest req;
    req.type_ = utils::data::TestRoute::JoinSession;
    req.user_id_ = std::move(user2_id_);
    debug_data_.user_id = user2_id_;
    req.session_id_ = 1;  // задавать руками
    std::shared_ptr<std::stringstream> ss = seabattle::utils::serializer::Serializer<
        seabattle::utils::data::TestDataRequest>::Serialize(req);

    network_client_->Run(ss, callback_);
    return 0;
}

size_t TestClient::TestStartGame_() {
    std::cout << "[TestClient] TestStartGame_" << std::endl;

    utils::data::TestDataRequest req;
    req.type_ = utils::data::TestRoute::StartGame;
    if (debug_data_.user_n == config::User_n::USER1) {
        req.session_id_ = user1_session_id_;
        req.user_id_ = user1_id_;
    } else {
        req.session_id_ = user2_session_id_;
        req.user_id_ = user2_id_;
    };
    req.map_ = std::move(debug_data_.debug_map);

    std::shared_ptr<std::stringstream> ss = seabattle::utils::serializer::Serializer<
        seabattle::utils::data::TestDataRequest>::Serialize(req);

    network_client_->Run(ss, callback_);

    return 0;
}

size_t TestClient::TestUpdateGame_() {
    std::cout << "[TestClient] TestUpdateGame_" << std::endl;

    utils::data::TestDataRequest req;
    req.type_ = utils::data::TestRoute::UpdateGame;
    if (debug_data_.user_n == config::User_n::USER1) {
        req.session_id_ = user1_session_id_;
        req.user_id_ = user1_id_;
    } else {
        req.session_id_ = user2_session_id_;
        req.user_id_ = user2_id_;
    };

    std::cout << "input x, y: ";
    std::cin >> req.point_.x_ >> req.point_.y_;

    std::shared_ptr<std::stringstream> ss = seabattle::utils::serializer::Serializer<
        seabattle::utils::data::TestDataRequest>::Serialize(req);

    network_client_->Run(ss, callback_);

    return 0;
}

size_t TestClient::TestEndGame_() {
    std::cout << "[TestClient] TestEndGame_" << std::endl;

    utils::data::TestDataRequest req;
    req.type_ = utils::data::TestRoute::EndGame;

    std::shared_ptr<std::stringstream> ss = seabattle::utils::serializer::Serializer<
        seabattle::utils::data::TestDataRequest>::Serialize(req);

    network_client_->Run(ss, callback_);
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

            std::cout << "[SERVER RESPONSE] resp->user_id_ " << resp->user_id_ << std::endl;
            std::cout << "[SERVER RESPONSE] resp->session_id_ " << resp->session_id_ << std::endl;
            std::cout << "[SERVER RESPONSE] resp->error_ " << static_cast<int>(resp->error_)
                      << std::endl;
            debug_data_.game_state = std::move(resp->game_state_);

            break;
        }
        case utils::data::TestRoute::UpdateGame: {
            std::cout << "[SERVER RESPONSE] UpdateGame" << std::endl;

            std::cout << "[SERVER RESPONSE] resp->game_state_.result_ "
                      << static_cast<int>(resp->game_state_.result_) << std::endl;
            std::cout << "[SERVER RESPONSE] resp->point_ " << resp->point_.x_ << resp->point_.y_
                      << std::endl;

            debug_data_.game_state = std::move(resp->game_state_);
            debug_data_.enemy_point = std::move(resp->point_);

            break;
        }
        case utils::data::TestRoute::JoinSession: {
            std::cout << "[SERVER RESPONSE] JoinSession" << std::endl;
            std::cout << "[SERVER RESPONSE] resp->session_id_ " << resp->session_id_ << std::endl;
            std::cout << "[SERVER RESPONSE] resp->error_ " << static_cast<int>(resp->error_)
                      << std::endl;
            //            user2_session_id_ = resp->session_id_;
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