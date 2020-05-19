#ifndef PROJECT_SERVER_DATA_H
#define PROJECT_SERVER_DATA_H

#include <msgpack.hpp>
#include <string>

enum class typeMsg {
    CreateSession = 1,
    UpdateGame,
    JoinSession,
    StartGame,
    CreateUser,
    EndGame
};

MSGPACK_ADD_ENUM(typeMsg)

enum class error {
    Success = 0,
    NotFound,
    Full,
    UserExist,
    Started,
    Wait,
    NotValidMap,
    EndGame
};

MSGPACK_ADD_ENUM(error)

struct AuthData {
    std::string login_;
    std::string password_;

    MSGPACK_DEFINE_MAP(login_, password_);

    AuthData() = default;
    AuthData(const std::string& login, const std::string& password): login_(login), password_(password) {}
};


enum class Result {
    Miss = 0,
    Hit,
    Kill,
    BadPoint
};

MSGPACK_ADD_ENUM(Result);

struct GameState {
    int nextStepId;
    Result result;
    bool EndGame;

    MSGPACK_DEFINE_MAP(nextStepId, result, EndGame);

    GameState() = default;
    GameState(int nextStepId, Result result, bool EndGame = false): nextStepId(nextStepId), result(result), EndGame(EndGame){}

    GameState& operator=(const GameState& rhs) {
        nextStepId = rhs.nextStepId;
        result = rhs.result;
        EndGame = rhs.EndGame;
        return *this;
    }
};

struct Point {
    size_t x;
    size_t y;

    MSGPACK_DEFINE_MAP(x, y);

    Point(size_t x, size_t y): x(x), y(y){}
    Point():x(0), y(0) {}

    const bool isValid() const {
        return x < 10 && y < 10;
    }
};

struct Ship {
    Point start;
    Point end;

    MSGPACK_DEFINE_MAP(start, end);

    Ship() = default;
    Ship(size_t startX, size_t startY, size_t endX, size_t endY):start(startX, startY), end(endX, endY){}

    const bool isValid() const {
        return (start.x == end.x || start.y == end.y) && start.isValid() && end.isValid();
    }

    const size_t length() const {
        return (start.x == end.x)?(end.y - start.y + 1):(end.x - start.x + 1);
    }
};

struct Map {
    std::map<int, Ship> ships;
    MSGPACK_DEFINE_MAP(ships);
    Map() = default;
};

struct EraseState {
    bool started = false;
    int winner_id = -1;

    MSGPACK_DEFINE_MAP(started, winner_id);

    EraseState() = default;
    EraseState(int winner_id): started(true), winner_id(winner_id) {}
    EraseState(bool started, int winner_id): started(started), winner_id(winner_id) {}

    EraseState& operator= (const EraseState& rhs) {
        started = rhs.started;
        winner_id = rhs.winner_id;
        return *this;
    }
};


struct Request {
    int user_id_;
    int session_id_;
    typeMsg type_;
    AuthData data_;
    Point point_;
    Map map_;

    MSGPACK_DEFINE_MAP(user_id_, session_id_, type_, data_, point_, map_);

    Request() = default;
    Request(const AuthData& data, typeMsg type): data_(data), type_(type) {}
};

struct Response {
    int user_id_;
    int session_id_;

    Point point_;
    GameState game_state_;
    EraseState erase_state_;

    error error_;

    MSGPACK_DEFINE_MAP(user_id_, session_id_, point_, game_state_ , erase_state_, error_);

    Response() = default;
};


#endif //PROJECT_SERVER_DATA_H
