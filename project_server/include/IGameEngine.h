#ifndef PROJECT_SERVER_IGAMEENGINE_H
#define PROJECT_SERVER_IGAMEENGINE_H

#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>

enum class Result {
    Miss = 0,
    Hit,
    Kill,
    BadPoint
};

struct GameState {
    int nextStepId;
    Result result;
    bool EndGame;

    GameState(int nextStepId, Result result, bool EndGame = false):nextStepId(nextStepId), result(result), EndGame(EndGame){}
};

struct Point {
    size_t x;
    size_t y;
    Point(size_t x, size_t y): x(x), y(y){}
    Point():x(0), y(0) {}

    const bool isValid() const {
        return x < 10 && y < 10;
    }
};

struct Ship {
    Point start;
    Point end;

    Ship(size_t startX, size_t startY, size_t endX, size_t endY):start(startX, startY), end(endX, endY){}

    const bool isValid() const {
        return (start.x == end.x || start.y == end.y) && start.isValid() && end.isValid();
    }

    const size_t length() const {
        if (start.x == end.x) {
            return end.y - start.y + 1;
        } else {
            return  end.x - start.x + 1;
        }
    }
};

struct Map {
    std::vector<Ship> ships;
};


class GameMap {
private:
    std::vector<std::vector<size_t>> cells;
    void flushResults(size_t start, size_t end, bool x, size_t constant);
public:
    GameMap();
    ~GameMap() = default;

    Result insertPoint(const Point& point);

    bool insertShip(const Ship& ship);
    void prepareMap();
};

class IGameEngine {
private:
    std::map<int, GameMap> userMaps;
    int stepId;
    bool validateMap(const Map& map, GameMap& gameMap);
public:
    IGameEngine(): stepId(0){}
    ~IGameEngine() = default;

    bool eraseId(int userId);

    std::shared_ptr<GameState> UpdateGame(int userId, const Point& point);

    bool insertMap(int userId, const Map& map);
    void setStep(int userId);
};


#endif //PROJECT_SERVER_IGAMEENGINE_H
