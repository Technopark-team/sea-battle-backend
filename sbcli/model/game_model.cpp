#include "game_model.h"

namespace seabattle {
namespace client {
namespace model {

GameModel::GameModel(std::shared_ptr<network::TCPClient>& network_client)
    : network_client_(network_client),
      user_id_(),
      session_id_(),
      current_step_(),
      enemy_current_step_(),
      user_map_(),
      enemy_killed_map_(),
      game_state_(),
      erase_state_(),
      error_() {
    callback_ = std::make_shared<std::function<size_t(std::stringstream&)>>(
        std::bind(&GameModel::GeneralCallback_, this, std::placeholders::_1));
}

size_t GameModel::GetSessionId(int& session_id) {
    session_id = std::move(session_id_);
    std::cout << session_id << std::endl;
    return 0;
}

size_t GameModel::GetUserId(int& user_id) {
    user_id = std::move(user_id_);
    std::cout << user_id << std::endl;
    return 0;
}

size_t GameModel::SetUserId(int user_id) {
    user_id_ = user_id;
    return 0;
}

size_t GameModel::SetCurrentStep(utils::data::TestPoint current_step) {
    current_step_ = std::move(current_step);
    return 0;
}

size_t GameModel::SetSessionId(int session_id) {
    session_id_ = std::move(session_id);
    std::cout << "session_id: " << session_id_ << std::endl;
    return 0;
}

size_t GameModel::GetEnemyCurrentStep(utils::data::TestPoint& enemy_current_step) {
    enemy_current_step = std::move(enemy_current_step_);
    return 0;
}
size_t GameModel::SetUserMap(utils::data::TestMap user_map) {
    user_map_ = std::move(user_map);
    return 0;
}
size_t GameModel::GetEnemyKilledMap(utils::data::TestMap& enemy_killed_map) {
    enemy_killed_map = std::move(enemy_killed_map_);
    return 0;
}
size_t GameModel::SetGameState(utils::data::TestGameState game_state) {
    game_state_ = std::move(game_state);
    return 0;
}
size_t GameModel::GetGameState(utils::data::TestGameState& game_state) {
    game_state = std::move(game_state_);
    return 0;
}
size_t GameModel::SetEraseState(utils::data::TestEraseState erase_state) {
    erase_state_ = std::move(erase_state);
    return 0;
}
size_t GameModel::GetEraseState(utils::data::TestEraseState& erase_state) {
    erase_state = std::move(erase_state_);
    return 0;
}

size_t GameModel::SetError(utils::data::TestError error) {
    error_ = error;
    return 0;
}

size_t GameModel::CreateSession() {
    utils::data::TestDataRequest req;
    req.type_ = utils::data::TestRoute::CreateSession;
    req.user_id_ = user_id_;
    std::shared_ptr<std::stringstream> ss = seabattle::utils::serializer::Serializer<
        seabattle::utils::data::TestDataRequest>::Serialize(req);

    network_client_->Run(ss, callback_, 1);
//    std::cout << "s_id create session: " << session_id_ << std::endl;
    return 0;
}
size_t GameModel::UpdateGame() {
    utils::data::TestDataRequest req;
    req.type_ = utils::data::TestRoute::CreateSession;
    req.user_id_ = user_id_;
    req.session_id_ = session_id_;

//    if (debug_mode) {
//
//    }
    std::cout << "input x, y: ";
    std::cin >> req.point_.x_ >> req.point_.y_;
    //    req.point_.x_ = 12;
    //    req.point_.y_ = 12;

    std::shared_ptr<std::stringstream> ss = seabattle::utils::serializer::Serializer<
        seabattle::utils::data::TestDataRequest>::Serialize(req);

    network_client_->Run(ss, callback_, 2);
    std::cout << "update session: " << session_id_ << std::endl;
    return 0;
}
size_t GameModel::JoinSession() {
    utils::data::TestDataRequest req;
    req.type_ = utils::data::TestRoute::JoinSession;
    req.user_id_ = user_id_;
    req.session_id_ = 1;
    std::shared_ptr<std::stringstream> ss = seabattle::utils::serializer::Serializer<
        seabattle::utils::data::TestDataRequest>::Serialize(req);
    network_client_->Run(ss, callback_, 2);
    std::cout << "req.user_id_ " << req.user_id_ << std::endl;
//    std::cout << "s_id join session: " << session_id_ << std::endl;
    return 0;
}
size_t GameModel::StartGame() {
    utils::data::TestDataRequest req;
    req.type_ = utils::data::TestRoute::StartGame;
    req.session_id_ = session_id_;
    req.user_id_ = user_id_;
//    req.map_ = user_map_;
    std::shared_ptr<std::stringstream> ss = seabattle::utils::serializer::Serializer<
        seabattle::utils::data::TestDataRequest>::Serialize(req);

    network_client_->Run(ss, callback_, 2);
//    std::cout << "request user_id: " << user_id_ << std::endl;
    std::cout << "map: " << user_map_.ships[5].start_.x_ << user_map_.ships[5].start_.y_
              << std::endl;
    return 0;
}
size_t GameModel::EndGame() {
    utils::data::TestDataRequest req;
    req.type_ = utils::data::TestRoute::EndGame;
    return 0;
}

size_t GameModel::GeneralCallback_(std::stringstream& response) {
    std::shared_ptr<utils::data::TestDataResponse> resp =
        utils::serializer::Serializer<utils::data::TestDataResponse>::Deserialize(
            response, response.str().size());

    std::cout << "response " << static_cast<int>(resp->type_) << std::endl;
    switch (resp->type_) {
        case utils::data::TestRoute::CreateSession: {
            std::cout << "GeneralCallback_ CreateSession" << std::endl;
            SetSessionId(resp->session_id_);
//            SetUserId(resp->user_id_);
            break;
        }
        case utils::data::TestRoute::StartGame: {
            std::cout << "GeneralCallback_ StartGame" << std::endl;
            std::cout << "resp->user_id_: " << resp->user_id_ << std::endl;
//            SetUserId(resp->user_id_);
            SetError(resp->error_);  // wait или started
            SetGameState(resp->game_state_);
            std::cout << "start" << static_cast<int>(error_) << std::endl;
            break;
        }
        case utils::data::TestRoute::UpdateGame: {
            std::cout << "GeneralCallback_ UpdateGame" << std::endl;
            SetGameState(resp->game_state_);
            break;
        }
        case utils::data::TestRoute::JoinSession: {
            std::cout << "GeneralCallback_ JoinSession" << std::endl;
            std::cout << resp->session_id_ << std::endl;
            SetError(resp->error_);  // должен получить Success
            std::cout << "resp->error_" << static_cast<int>(resp->error_) << std::endl;
            break;
        }
        case utils::data::TestRoute::EndGame: {
            std::cout << "GeneralCallback_ EndGame" << std::endl;
            break;
        }
    }
    return 0;
}

}  // namespace model
}  // namespace client
}  // namespace seabattle