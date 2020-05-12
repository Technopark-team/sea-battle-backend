#ifndef PROJECT_SERVER_IGAMEENGINE_H
#define PROJECT_SERVER_IGAMEENGINE_H

#include <map>
#include <vector>
#include <iostream>

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
    bool flushResults(size_t start, size_t end, bool x, size_t constant);
public:
    GameMap();
    bool insertPoint(const Point& point);
    bool insertShip(const Ship& ship);

    void print() {
        for (auto& line: cells) {
            for (auto& call: line) {
                std::cout << call << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "---------------" << std::endl;
    }

    ~GameMap() = default;
};

class IGameEngine {
private:
    std::map<int, GameMap> userMaps;
    bool validateMap(const Map& map, GameMap& gameMap);
public:
    bool insertMap(int userId, const Map& map);
};


#endif //PROJECT_SERVER_IGAMEENGINE_H
