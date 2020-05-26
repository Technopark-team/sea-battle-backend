#include "game_model.h"

namespace seabattle {
namespace client {
namespace model {

GameModel::GameModel(std::shared_ptr<network::TCPClient>& network_client) {}

size_t GameModel::GetSessionId(int& session_id) {
    session_id = std::move(session_id_);
    return 0;
}

size_t GameModel::SetCurrentStep(utils::data::TestPoint current_step) {
    current_step_ = std::move(current_step);
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

size_t GameModel::CreateSession() { return 0; }
size_t GameModel::UpdateGame() { return 0; }
size_t GameModel::JoinSession() { return 0; }
size_t GameModel::StartGame() { return 0; }
size_t GameModel::Enter() { return 0; }
size_t GameModel::EndGame() { return 0; }

size_t GameModel::GeneralCallback_(std::stringstream& response) {
    std::shared_ptr<utils::data::TestDataResponse> resp =
        utils::serializer::Serializer<utils::data::TestDataResponse>::Deserialize(
            response, response.str().size());

    switch (resp->type_) {
        case utils::data::TestRoute::CreateSession: {
            session_id_ = resp->session_id_;
            break;
        }
        case utils::data::TestRoute::StartGame: {
            break;
        }
        case utils::data::TestRoute::UpdateGame: {
            break;
        }
        case utils::data::TestRoute::JoinSession: {
            break;
        }
        case utils::data::TestRoute::Enter: {
            break;
        }
        case utils::data::TestRoute::EndGame: {
            break;
        }
    }
    return 0;
}

}  // namespace model
}  // namespace client
}  // namespace seabattle