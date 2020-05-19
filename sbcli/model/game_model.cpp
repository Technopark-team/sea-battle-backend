#include "game_model.h"

namespace seabattle {
namespace client {
namespace model {

GameModel::GameModel(std::shared_ptr<network::TCPClient>& network_client) {}
size_t GameModel::PostGameSingle() { return 0; }
size_t GameModel::PostGameMulti() { return 0; }
size_t GameModel::PutGameSave() { return 0; }
size_t GameModel::GetGameOpen() { return 0; }
size_t GameModel::PostGameStep() { return 0; }
size_t GameModel::GetGameState() { return 0; }
size_t GameModel::GetGameAll() { return 0; }
size_t GameModel::PutGameStop() { return 0; }
size_t GameModel::SetCurrentStep(utils::data::UserStep user_step) { return 0; }
size_t GameModel::GetEnemyState(utils::data::GameStatus& enemy_step_status) { return 0; }
size_t GameModel::SetShips(utils::data::PlayerMap player_map) { return 0; }
size_t GameModel::GetShips(utils::data::PlayerMap& player_map) { return 0; }
size_t GameModel::GetGameId(utils::data::GameData& game_data) { return 0; }
size_t GameModel::GetStateShips(utils::data::PlayerStateMap& player_state_map) { return 0; }
size_t GameModel::SetStateShips(utils::data::PlayerStateMap player_state_map) { return 0; }

size_t GameModel::GeneralCallback_(std::stringstream& response) { return 0; }

}  // namespace model
}  // namespace client
}  // namespace seabattle