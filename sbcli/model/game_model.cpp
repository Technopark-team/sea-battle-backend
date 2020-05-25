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
size_t GameModel::SetCurrentStep(utils::data::TestPoint user_step) { return 0; }
size_t GameModel::SetShips(utils::data::TestMap player_map) { return 0; }
size_t GameModel::GetShips(utils::data::TestMap& player_map) { return 0; }
size_t GameModel::GetGameId(int& session_id) { return 0; }

size_t GameModel::GeneralCallback_(std::stringstream& response) { return 0; }

}  // namespace model
}  // namespace client
}  // namespace seabattle