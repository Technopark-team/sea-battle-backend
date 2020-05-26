#ifndef PROJECT_SERVER_DATA_H
#define PROJECT_SERVER_DATA_H

#include <msgpack.hpp>
#include <string>

enum class Route {
    CreateSession = 1,
    UpdateGame,
    JoinSession,
    StartGame,
    CreateUser,
    Enter,
    EndGame
};

MSGPACK_ADD_ENUM(Route)

enum class Error {
    Success = 0,
    NotFound,
    Full,
    UserExist,
    InvalidLogIn,
    Started,
    Wait,
    NotValidMap,
    EndGame
};

MSGPACK_ADD_ENUM(Error)

struct AuthData {
    std::string login_;
    std::string password_;

    MSGPACK_DEFINE_MAP(login_, password_)

    AuthData() = default;
    AuthData(const std::string& login, const std::string& password): login_(login), password_(password) {}
};


enum class Result {
    Miss = 0,
    Hit,
    Kill,
    BadPoint
};

MSGPACK_ADD_ENUM(Result)

struct GameState {
    int next_step_id_;
    Result result_;
    bool end_game_;

    MSGPACK_DEFINE_MAP(next_step_id_, result_, end_game_)

    GameState() = default;
    GameState(int next_step_id, Result result, bool end_game = false): next_step_id_(next_step_id), result_(result), end_game_(end_game){}

    GameState& operator=(const GameState& rhs) {
        next_step_id_ = rhs.next_step_id_;
        result_ = rhs.result_;
        end_game_ = rhs.end_game_;
        return *this;
    }
};

struct Point {
    size_t x_;
    size_t y_;

    MSGPACK_DEFINE_MAP(x_, y_)

    Point(size_t x, size_t y): x_(x), y_(y){}
    Point():x_(0), y_(0) {}

    const bool isValid() const {
        return x_ < 10 && y_ < 10;
    }
};

struct Ship {
    Point start_;
    Point end_;

    MSGPACK_DEFINE_MAP(start_, end_)

    Ship() = default;
    Ship(size_t start_x, size_t start_y, size_t end_x, size_t end_y):start_(start_x, start_y), end_(end_x, end_y) {}
    Ship(const Point& start, const Point& end): start_(start), end_(end) {}

    const bool IsValid() const {
        return (start_.x_ == end_.x_ || start_.y_ == end_.y_) && start_.isValid() && end_.isValid();
    }

    const size_t Length() const {
        return (start_.x_ == end_.x_)?(end_.y_ - start_.y_ + 1):(end_.x_ - start_.x_ + 1);
    }
};

struct Map {
    std::map<int, Ship> ships;
    MSGPACK_DEFINE_MAP(ships)
    Map() = default;
};

struct EraseState {
    bool started_ = false;
    int winner_id_ = -1;

    MSGPACK_DEFINE_MAP(started_, winner_id_)

    EraseState() = default;
    EraseState(int winner_id): started_(true), winner_id_(winner_id) {}
    EraseState(bool started, int winner_id): started_(started), winner_id_(winner_id) {}

    EraseState& operator= (const EraseState& rhs) {
        started_ = rhs.started_;
        winner_id_ = rhs.winner_id_;
        return *this;
    }
};

struct DataRequest {
    int user_id_;
    int session_id_;
    Route type_;
    AuthData data_;
    Point point_;
    Map map_;

    MSGPACK_DEFINE_MAP(user_id_, session_id_, type_, data_, point_, map_)

    DataRequest() = default;
    DataRequest(const AuthData& data, Route type): type_(type), data_(data) {}
};

struct DataResponse {
    int user_id_;
    int session_id_;
    Route type_;
    Point point_;
    GameState game_state_;
    EraseState erase_state_;

    Error error_;

    MSGPACK_DEFINE_MAP(user_id_, session_id_, type_, point_, game_state_ , erase_state_, error_)

    DataResponse() = default;
};


#endif //PROJECT_SERVER_DATA_H
