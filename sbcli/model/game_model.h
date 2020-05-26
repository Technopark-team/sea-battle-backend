#ifndef SEABATTLE_GAME_MODEL_H
#define SEABATTLE_GAME_MODEL_H

#include <memory>
#include "model_inteface.h"
#include "network/network.h"
#include "sbcli/config/config.h"
#include "sbutils/serialization/serializer.h"

namespace seabattle {
namespace client {
namespace model {

// TODO: добавить документацию к методам и свойствам

class GameModel : public IModel {
 public:
    explicit GameModel(std::shared_ptr<network::TCPClient> &network_client);
    ~GameModel() = default;

    size_t GetSessionId(int &session_id);
    size_t SetCurrentStep(utils::data::TestPoint current_step);
    size_t GetEnemyCurrentStep(utils::data::TestPoint &current_enemy_step);
    size_t SetUserMap(utils::data::TestMap user_map);
    size_t GetEnemyKilledMap(utils::data::TestMap &enemy_killed_map);
    size_t SetGameState(utils::data::TestGameState game_state);
    size_t GetGameState(utils::data::TestGameState &game_state);
    size_t SetEraseState(utils::data::TestEraseState erase_state);
    size_t GetEraseState(utils::data::TestEraseState &erase_state);

    size_t CreateSession() override;
    size_t UpdateGame() override;
    size_t JoinSession() override;
    size_t StartGame() override;
    size_t Enter() override;
    size_t EndGame() override;

 private:
    size_t GeneralCallback_(std::stringstream &response) override;

    int user_id_;
    int session_id_;
    utils::data::TestPoint current_step_;
    utils::data::TestPoint enemy_current_step_;
    utils::data::TestMap user_map_;
    utils::data::TestMap enemy_killed_map_;
    utils::data::TestGameState game_state_;
    utils::data::TestEraseState erase_state_;

    std::shared_ptr<network::TCPClient> network_client_;
    std::shared_ptr<std::function<size_t(std::stringstream &)>> callback_;
};

}  // namespace model
}  // namespace client
}  // namespace seabattle

#endif  // SEABATTLE_GAME_MODEL_H
