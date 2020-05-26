#include "IGameEngine.h"

std::shared_ptr<GameMap> IGameEngine::ValidateMap(const Map& map) {
    if (map.ships.size() != 10) {
        return nullptr;
    }

    Counters valid = Counters(4, 3, 2, 1);
    Counters ships = Counters();
    std::shared_ptr<GameMap> gm = std::make_shared<GameMap>();
    for (auto& ship: map.ships) {
        bool result = gm->InsertShip(ship.first, ship.second);
        if (!result) {
            return nullptr;
        }
        ships.Insert(ship.second.Length());
    }
   if (!(valid == ships)) {
       return nullptr;
   }
   return gm;
}

std::shared_ptr<GameMap> IGameEngine::CreateMap() {
    return std::make_shared<GameMap>();
}

bool IGameEngine::InsertMap(int user_id, const Map& map) {
    std::shared_ptr<GameMap> gm = ValidateMap(map);
    if (gm) {
        user_maps_.insert({user_id, *gm});
        return true;
    }
    return false;
}

void IGameEngine::SetStep(int user_id) {
    step_id_ = user_id;
}

std::shared_ptr<GameState> IGameEngine::UpdateGame(int user_id, const Point& point) {
    if (user_id != step_id_) {
        return nullptr;
    }

    int id = user_maps_.begin()->first;
    if (id == user_id) {
        id = user_maps_.end()->first;
    }

    Result result = user_maps_.find(id)->second.InsertPoint(point);

    if (result == Result::BadPoint) {
        return nullptr;
    } else if (result == Result::Miss) {
        step_id_ = id;
        return std::make_shared<GameState>(step_id_, result);
    } else if (result == Result::Hit) {
        return std::make_shared<GameState>(step_id_, result);
    } else {
        int count = user_maps_.find(id)->second.Count();
        if (count == 0) {
            int winner_id = user_id;
            EndGame(user_id, winner_id);
            return std::make_shared<GameState>(step_id_, result, true);
        }
        return std::make_shared<GameState>(step_id_, result);
    }
}

bool IGameEngine::EraseId(int user_id) {
    return user_maps_.erase(user_id);
}

void IGameEngine::EndGame(int user_id, int& winner_id) {
    int id = user_maps_.begin()->first;

    if (id == user_id) {
        id = user_maps_.end()->first;
    }

    if (winner_id == -1) {
        winner_id = id;
    }

    user_maps_.clear();
    running_ = false;
}

void IGameEngine::StartGame() {
    running_ = true;
}


GameMap::GameMap() {
    for (auto& row: cells_) {
        for (auto& col: row) {
            col = std::make_pair(0, 0);
        }
    }
}

GameMap::GameMap(const GameMap& rhs) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cells_[i][j].first = rhs.cells_[i][j].first;
            cells_[i][j].second = rhs.cells_[i][j].second;
        }
    }
    for (auto& ship: rhs.game_ships_) {
        game_ships_.insert(ship);
    }
}

Result GameMap::InsertPoint(const Point& point) {
    if (!point.isValid()) {
        return Result::BadPoint;
    }
    if (cells_.at(point.y_).at(point.x_).first == 1) {
        auto it = game_ships_.find(cells_[point.y_][point.x_].second);
        it->second = it->second - 1;
        cells_[point.y_][point.x_].first = 2;
        if (it->second < 1) {
            game_ships_.erase(it);
            return Result::Kill;
        }
        return Result::Hit;
    }
    return Result::Miss;
}

bool GameMap::InsertShip(int id, const Ship& ship) {
    if (!ship.IsValid()) {
        return false;
    }

    if (ship.start_.x_ == ship.end_.x_) {
        int start = ship.start_.y_;
        int x = ship.start_.x_;

        if (start - 1 >= 0) {
            if (cells_[start - 1][x].first == 1) {
                return false;
            }

            if (x - 1 >= 0) {
                if (cells_[start - 1][x - 1].first == 1) {
                    return false;
                }
            }

            if (x + 1 <= 9) {
                if (cells_[start - 1][x + 1].first == 1) {
                    return false;
                }
            }
        }

        while (start <= ship.end_.y_) {
            if (x - 1 >= 0) {
                if (cells_[start][x - 1].first == 1) {
                    return false;
                }
            }
            if (x + 1 <= 9) {
                if (cells_[start][x + 1].first == 1) {
                    return false;
                }
            }

            if (cells_[start][x].first == 1) {
                return false;
            }
            cells_[start][x].first = 1;
            cells_[start][x].second = id;

            start++;
        }

        if (start <= 9) {
            if (cells_[start][x].first == 1) {
                return false;
            }
            if (x - 1 >= 0) {
                if (cells_[start][x - 1].first == 1) {
                    return false;
                }
            }
            if (x + 1 <= 9) {
                if (cells_[start][x + 1].first == 1) {
                    return false;
                }
            }
        }
    } else {

        int start = ship.start_.x_;
        int y = ship.start_.y_;

        if (start - 1 >= 0) {
            if (cells_[y][start - 1].first == 1) {
                return false;
            }
            if (y - 1 >= 0) {
                if (cells_[y - 1][start - 1].first == 1) {
                    return false;
                }
            }
            if (y + 1 <= 9) {
                if (cells_[y + 1][start - 1].first == 1) {
                    return false;
                }
            }
        }

        while (start <= ship.end_.x_) {
            if (y - 1 >= 0) {
                if (cells_[y - 1][start].first == 1) {
                    return false;
                }
            }
            if (y + 1 <= 9) {
                if (cells_[y + 1][start].first == 1) {
                    return false;
                }
            }
            if (cells_[y][start].first == 1) {
                return false;
            }
            cells_[y][start].first = 1;
            cells_[y][start].second = id;

            start++;
        }

        if (start <= 9) {
            if (cells_[y][start].first == 1) {
                return false;
            }

            if (y - 1 >= 0) {
                if (cells_[y - 1][start].first == 1) {
                    return false;
                }
            }

            if (y + 1 <= 9) {
                if (cells_[y + 1][start].first == 1) {
                    return false;
                }
            }
        }
    }
    game_ships_.insert({id, ship.Length()});
    return true;
}

int GameMap::Count() {
    return game_ships_.size();
}

/*void GameMap::prepareMap() {
    for (auto& line: cells) {
        std::replace(line.begin(),line.end(), 2, 0);
    }
}*/
