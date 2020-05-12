#include "IGameEngine.h"

bool IGameEngine::validateMap(const Map& map, GameMap& gameMap) {
    for (auto& ship: map.ships) {
        bool result = gameMap.insertShip(ship);
        if (!result) {
            return false;
        }
    }
    // todo: check count of ships and refuse 2 from map after validation
    return true;
}

bool IGameEngine::insertMap(int userId, const Map &map) {
    GameMap gameMap = GameMap();
    if (validateMap(map, gameMap)) {
        userMaps.insert({userId, gameMap});
        return true;
    }
    return false;
}

GameMap::GameMap() {
    cells.resize(10);
    for (auto& line: cells) {
        line.assign(10, 0);
    }
}

bool GameMap::insertPoint(const Point& point) {
    if (!point.isValid() && cells[point.y][point.x] != 0) {
        return false;
    }
    cells[point.y][point.x] = 1;
    return true;
}

bool GameMap::flushResults(size_t start, size_t end, bool x, size_t constant) {
    if (x) {
        int i = end;
        while (i >= start) {
            cells[i][constant] = 0;
            i--;
        }
    } else {
        int i = end;
        while (i >= start) {
            cells[constant][i] = 0;
            i--;
        }
    }
}

bool GameMap::insertShip(const Ship& ship) {
    if (!ship.isValid()) {
        return false;
    }

    if (ship.start.x == ship.end.x) {
        int start = ship.start.y;
        int x = ship.start.x;

        if (start - 1 >= 0) {
            if (cells[start - 1][x] != 1) {
                cells[start - 1][x] = 2;
            } else {
                return false;
            }
            if (x - 1 >= 0) {
                if (cells[start - 1][x - 1] != 1) {
                    cells[start - 1][x - 1] = 2;
                } else {
                    return false;
                }
            }
            if (x + 1 <= 9) {
                if (cells[start - 1][x + 1] != 1) {
                    cells[start - 1][x + 1] = 2;
                } else {
                    return false;
                }
            }
        }

        while (start <= ship.end.y) {
            if (x - 1 >= 0) {
                if (cells[start][x - 1] != 1) {
                    cells[start][x - 1] = 2;
                } else {
                    flushResults(ship.start.y, start - 1, true, x);
                    return false;
                }
            }
            if (x + 1 <= 9) {
                if (cells[start][x + 1] != 1) {
                    cells[start][x + 1] = 2;
                } else {
                    flushResults(ship.start.y, start - 1, true, x);
                    return false;
                }
            }
            if (cells[start][x] == 1) {
                flushResults(ship.start.y, start - 1, true, x);
                return false;
            }

            cells[start][x] = 1;
            start++;
        }

        if (start <= 9) {
            if (cells[start][x] != 1) {
                cells[start][x] = 2;
            } else {
                flushResults(ship.start.y, start - 1, true, x);
                return false;
            }

            if (x - 1 >= 0) {
                if (cells[start][x - 1] != 1) {
                    cells[start][x - 1] = 2;
                } else {
                    flushResults(ship.start.y, start - 1, true, x);
                    return false;
                }
            }
            if (x + 1 <= 9) {
                if (cells[start][x + 1] != 1) {
                    cells[start][x + 1] = 2;
                } else {
                    flushResults(ship.start.y, start - 1, true, x);
                    return false;
                }
            }
        }

    } else {

        int start = ship.start.x;
        int y = ship.start.y;

        if (start - 1 >= 0) {
            if (cells[y][start - 1] != 1) {
                cells[y][start - 1] = 2;
            } else {
                return false;
            }
            if (y - 1 >= 0) {
                if (cells[y - 1][start - 1] != 1) {
                    cells[y - 1][start - 1] = 2;
                } else {
                    return false;
                }
            }
            if (y + 1 <= 9) {
                if (cells[y + 1][start - 1] <= 9) {
                    cells[y + 1][start - 1] = 2;
                } else {
                    return false;
                }
            }
        }

        while (start <= ship.end.x) {
            if (y - 1 >= 0) {
                if (cells[y - 1][start] != 1) {
                    cells[y - 1][start] = 2;
                } else {
                    flushResults(ship.start.x, start - 1, false, y);
                    return false;
                }
            }
            if (y + 1 <= 9) {
                if (cells[y + 1][start] != 1) {
                    cells[y + 1][start] = 2;
                } else {
                    flushResults(ship.start.x, start - 1, false, y);
                    return false;
                }
            }
            if (cells[y][start] == 1) {
                flushResults(ship.start.x, start - 1, false, y);
                return false;
            }
            cells[y][start] = 1;
            start++;
        }

        if (start <= 9) {
            if (cells[y][start] != 1) {
                cells[y][start] = 2;
            } else {
                flushResults(ship.start.x, start - 1, false, y);
                return false;
            }

            if (y - 1 >= 0) {
                if (cells[y - 1][start] != 1) {
                    cells[y - 1][start] = 2;
                } else {
                    flushResults(ship.start.x, start - 1, false, y);
                    return false;
                }
            }

            if (y + 1 <= 9) {
                if (cells[y + 1][start] <= 9) {
                    cells[y + 1][start] = 2;
                } else {
                    flushResults(ship.start.x, start - 1, false, y);
                    return false;
                }
            }
        }
    }
    return true;
}

