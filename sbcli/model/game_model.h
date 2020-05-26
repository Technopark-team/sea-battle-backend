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
    // TODO: реализовать SetInterval для этого запроса
    size_t GetGameState() override;
    size_t GetGameAll() override;
    size_t PutGameStop() override;

    size_t SetCurrentStep(utils::data::TestPoint user_step);

    size_t SetShips(utils::data::TestMap player_map);
    size_t GetShips(utils::data::TestMap &player_map);

    size_t GetGameId(int &session_id);

 private:
    size_t GeneralCallback_(std::stringstream& response) override;

    int session_id_;
    utils::data::TestPoint current_step_;
    utils::data::TestPoint enemy_current_step_;
    utils::data::TestMap user_map_;
    utils::data::TestMap enemy_killed_map_;

    std::shared_ptr<network::TCPClient> network_client_;
    std::shared_ptr<std::function<size_t(std::stringstream&)>> callback_;
};

}  // namespace model
}  // namespace client
}  // namespace seabattle

#endif  // SEABATTLE_GAME_MODEL_H
