#ifndef SEABATTLE_SBCLI_COMPONENTS_GAME_GAME_H_
#define SEABATTLE_SBCLI_COMPONENTS_GAME_GAME_H_

#include <ncurses.h>
#include <memory>
#include "sbcli/blocks/field.h"
#include "sbcli/blocks/ships.h"
#include "sbcli/config/config.h"
#include "sbutils/data/test_data.h"

namespace seabattle {
namespace client {
namespace component {

enum class YesNo {
    DEFAULT = -1,
    YES = 1,
    NO,
};

class GameMenu {
 public:
    GameMenu();
    ~GameMenu() = default;

    size_t GetMap(utils::data::TestMap &player_map, config::UserCommandId &exit);
    size_t GetStep(utils::data::TestPoint &player_point, config::UserCommandId &exit);

 private:
    size_t Draw_(size_t item);
    size_t SetShip(size_t item, utils::data::TestPoint &start, utils::data::TestPoint &end,
                 config::UserCommandId &cell_exit);
    size_t SetShipDirection(size_t item, int x, int y, utils::data::TestPoint &end,
                          config::UserCommandId &cell_direction_exit);
    size_t InitStaticFields();
    size_t TransformCoordinates(int x, int y, utils::data::TestPoint &point);

    size_t MakeBaseColor(int item, int x, int y);

    size_t IsPlayerUPEdge(int y, YesNo &check);
    size_t IsPlayerDOWNEdge(int y, YesNo &check);
    size_t IsPlayerLEFTEdge(int x, YesNo &check);
    size_t IsPlayerRIGHTEdge(int x, YesNo &check);

    size_t IsOpponentUPEdge(int y, YesNo &check);
    size_t IsOpponentDOWNEdge(int y, YesNo &check);
    size_t IsOpponentLEFTEdge(int x, YesNo &check);
    size_t IsOpponentRIGHTEdge(int x, YesNo &check);

    size_t IsEmptyCell(int x, int y, YesNo &check);
    size_t InsertCell(utils::data::TestPoint &start, utils::data::TestPoint &end);

    std::map<int, bool> set_ships;
    std::vector<std::pair<int, int>> nonempty_cells;

    block::ShipsView menu;
};

}  // namespace component
}  // namespace client
}  // namespace seabattle

#endif  // SEABATTLE_SBCLI_COMPONENTS_GAME_GAME_H_
