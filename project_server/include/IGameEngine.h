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

    void insert(int length) {
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
    std::vector<std::vector<std::pair<size_t, int>>> cells;
    std::unordered_map<int, size_t> game_ships_;
    void flushResults(size_t start, size_t end, bool x, size_t constant);
public:
    GameMap();
    ~GameMap() = default;

    Result insertPoint(const Point& point);
    int Count();

    bool insertShip(int id, const Ship& ship);
    //void prepareMap();
};



class IGameEngine {
private:
    std::map<int, GameMap> userMaps;
    int stepId;
    bool validateMap(const Map& map, GameMap& gameMap);
    bool running;
public:
    IGameEngine(): stepId(0), running(false) {}
    ~IGameEngine() = default;

    void EndGame(int user_id, int& winner_id);
    void StartGame();

    bool eraseId(int userId);

    std::shared_ptr<GameState> UpdateGame(int userId, const Point& point);

    bool insertMap(int userId, const Map& map);
    void setStep(int userId);
};


#endif //PROJECT_SERVER_IGAMEENGINE_H
