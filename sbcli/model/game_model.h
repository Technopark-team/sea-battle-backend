#ifndef SEABATTLE_GAME_MODEL_H
#define SEABATTLE_GAME_MODEL_H

#include <memory>
#include "sbcli/config/config.h"
#include "sbutils/serialization/serializer.h"
#include "model_inteface.h"
#include "network/network.h"

namespace seabattle {
namespace client {
namespace model {

// TODO: добавить документацию к методам и свойствам

class GameModel : public IModel {
 public:
    explicit GameModel(std::shared_ptr<network::TCPClient> &network_client);
    ~GameModel() = default;

    size_t PostGameSingle() override;
    size_t PostGameMulti() override;
    size_t PutGameSave() override;
    size_t GetGameOpen() override;
    size_t PostGameStep() override;
    size_t GetGameState() override;
    size_t GetGameAll() override;
    size_t PutGameStop() override;

    size_t SetCurrentStep(utils::data::UserStep user_step);
    size_t GetEnemyState(utils::data::GameStatus &enemy_game_status);

    size_t SetShips(utils::data::PlayerMap player_map);
    size_t GetShips(utils::data::PlayerMap &player_map);

    size_t GetGameId(utils::data::GameData &game_data);

    size_t GetStateShips(utils::data::PlayerStateMap &player_state_map);
    size_t SetStateShips(utils::data::PlayerStateMap player_state_map);

 private:
    size_t GeneralCallback_(std::stringstream& response) override;

    utils::data::GameData game_data_;
    utils::data::UserStep current_step_;
    utils::data::UserStep enemy_current_step_;
    utils::data::PlayerMap user_map_;
    utils::data::PlayerStateMap user_state_map_;
    utils::data::PlayerMap enemy_killed_map_;
    utils::data::PlayerStateMap enemy_state_map_;

    std::shared_ptr<network::TCPClient> network_client_;
    std::shared_ptr<std::function<size_t(std::stringstream&)>> callback_;
};

}  // namespace model
}  // namespace client
}  // namespace seabattle

#endif  // SEABATTLE_GAME_MODEL_H
