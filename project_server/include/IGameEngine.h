#ifndef PROJECT_SERVER_IGAMEENGINE_H
#define PROJECT_SERVER_IGAMEENGINE_H

#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>

#include "Data.h"

struct Counters {
    size_t one_;
    size_t two_;
    size_t three_;
    size_t four_;

    Counters(): one_(0), two_(0), three_(0), four_(0) {}
    Counters(size_t one, size_t two, size_t three, size_t four): one_(one), two_(two), three_(three), four_(four) {}

    void Insert(int length) {
        switch (length) {
            case 1:
                one_ += 1;
                break;
            case 2:
                two_ += 1;
                break;
            case 3:
                three_ += 1;
                break;
            case 4:
                four_ += 1;
                break;
            default:
                break;
        }
    }

    bool operator==(const Counters& rhs) {
        return one_ == rhs.one_ && two_ == rhs.two_ && three_ == rhs.three_ && four_ == rhs.four_;
    }
};



class GameMap {
private:
    std::array<std::array<std::pair<size_t, int>, 10>, 10> cells_;
    std::unordered_map<int, size_t> game_ships_;
public:
    GameMap();
    GameMap(const GameMap& rhs);

    ~GameMap() = default;

    Result InsertPoint(const Point& point);
    int Count();

    bool InsertShip(int id, const Ship& ship);
    //void prepareMap();
};



class IGameEngine {
private:
    int step_id_;
    bool running_;
    std::map<int, GameMap> user_maps_;
public:
    IGameEngine(): step_id_(0), running_(false) {}
    ~IGameEngine() = default;

    void EndGame(int user_id, int& winner_id);
    void StartGame();

    bool EraseId(int user_id);

    std::shared_ptr<GameState> UpdateGame(int user_id, const Point& point);

    std::shared_ptr<GameMap> CreateMap();
    bool InsertMap(int user_id, const Map& map);
    std::shared_ptr<GameMap> ValidateMap(const Map& map);
    void SetStep(int user_id);
};


#endif //PROJECT_SERVER_IGAMEENGINE_H
