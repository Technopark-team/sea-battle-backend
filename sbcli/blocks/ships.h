#ifndef SEABATTLE_SBCLI_BLOCKS_SHIPS_H_
#define SEABATTLE_SBCLI_BLOCKS_SHIPS_H_

#include "sbutils/data/test_data.h"

namespace seabattle {
namespace client {
namespace block {

enum ShipAttribute {
    DEFAULT = -1,
    WAIT = 1,
    SET,
    FULL,
    STRICK,
    KILLED,
};

struct UserListName {
//    const char name[64] = "Ваши корабли:";
    const char name[64] = "Your ships:";
};

struct EnemyListName {
//    const char name[64] = "Корабли противника:";
    const char name[64] = "Enemy's ships:";
};


struct ShipsView {
//    const char name[10][64] = {"1.  Четырехпалубный - ▒│▒│▒│▒", "2.  Трехпалубный    - ▒│▒│▒ ",
//                               "3.  Трехпалубный    - ▒│▒│▒  ", "4.  Двухпалубный    - ▒│▒   ",
//                               "5.  Двухпалубный    - ▒│▒    ", "6.  Двухпалубный    - ▒│▒   ",
//                               "7.  Однопалубный    - ▒      ", "8.  Однопалубный    - ▒     ",
//                               "9.  Однопалубный    - ▒      ", "10. Однопалубный    - ▒     "};
    const char name[10][64] = {"1.  Four deck   - @|@|@|@", "2.  Three deck  - @|@|@  ",
                               "3.  Three deck  - @|@|@  ", "4.  Double deck - @|@    ",
                               "5.  Double deck - @|@    ", "6.  Double deck - @|@    ",
                               "7.  Single deck - @      ", "8.  Single deck - @      ",
                               "9.  Single deck - @      ", "10. Single deck - @      "};
    const int len = 10;
    std::map<size_t, size_t> ships = {
        {0, ShipAttribute::DEFAULT},
        {1, ShipAttribute::DEFAULT},
        {2, ShipAttribute::DEFAULT},
        {3, ShipAttribute::DEFAULT},
        {4, ShipAttribute::DEFAULT},
        {5, ShipAttribute::DEFAULT},
        {6, ShipAttribute::DEFAULT},
        {7, ShipAttribute::DEFAULT},
        {8, ShipAttribute::DEFAULT},
        {9, ShipAttribute::DEFAULT},
    };
    utils::data::TestMap map;

    ShipsView() = default;
    ShipsView(std::map<size_t, size_t> ships, utils::data::TestMap map)
        : ships(std::move(ships)), map(std::move(map)) {}
};

}  // namespace block
}  // namespace client
}  // namespace seabattle

#endif  // SEABATTLE_SBCLI_BLOCKS_SHIPS_H_
