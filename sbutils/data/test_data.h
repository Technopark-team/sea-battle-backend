#ifndef SEABATTLE_SBUTILS_DATA_TEST_DATA_H_
#define SEABATTLE_SBUTILS_DATA_TEST_DATA_H_

#include <msgpack.hpp>
#include <string>

namespace seabattle {
namespace utils {
namespace data {

enum class TestRoute {
    CreateSession = 1,
    UpdateGame,
    JoinSession,
    StartGame,
    CreateUser,
    Enter,
    EndGame
};

enum class TestError {
    Success = 1,
    NotFound,
    Full,
    UserExist,
    InvalidLogIn,
    Started,
    Wait,
    NotValidMap,
    EndGame
};

struct TestAuthData {
    std::string login_;
    std::string password_;

    MSGPACK_DEFINE_MAP(login_, password_)

    TestAuthData() = default;
    TestAuthData(const std::string& login, const std::string& password)
        : login_(login), password_(password) {}
};

enum class TestResult { Default = -1, Miss = 1, Hit, Kill, BadPoint };

struct TestPoint {
    size_t x_;
    size_t y_;

    MSGPACK_DEFINE_MAP(x_, y_)

    TestPoint(size_t x, size_t y) : x_(x), y_(y) {}
    TestPoint() : x_(-1), y_(-1) {}

    const bool isValid() const { return x_ < 10 && y_ < 10; }
};

struct TestShip {
    TestPoint start_;
    TestPoint end_;

    MSGPACK_DEFINE_MAP(start_, end_)

    TestShip() = default;
    TestShip(size_t start_x, size_t start_y, size_t end_x, size_t end_y)
        : start_(start_x, start_y), end_(end_x, end_y) {}
    TestShip(const TestPoint& start, const TestPoint& end) : start_(start), end_(end) {}

    const bool IsValid() const {
        return (start_.x_ == end_.x_ || start_.y_ == end_.y_) && start_.isValid() && end_.isValid();
    }

    const size_t Length() const {
        return (start_.x_ == end_.x_) ? (end_.y_ - start_.y_ + 1) : (end_.x_ - start_.x_ + 1);
    }
};

struct TestMap {
    std::map<int, TestShip> ships;
    MSGPACK_DEFINE_MAP(ships)
    TestMap() = default;
};

struct TestGameState {
    int next_step_id_ = -1;
    TestResult result_ = TestResult::Default;
    TestShip killed_ship_;
    bool end_game_;

    MSGPACK_DEFINE_MAP(next_step_id_, result_, killed_ship_, end_game_)

    TestGameState() = default;
    TestGameState(int next_step_id, TestResult result, const TestShip& killed_ship,
                  bool end_game = false)
        : next_step_id_(next_step_id),
          killed_ship_(killed_ship),
          result_(result),
          end_game_(end_game) {}
    TestGameState(int next_step_id, TestResult result, bool end_game = false)
        : next_step_id_(next_step_id), result_(result), end_game_(end_game) {}

    TestGameState& operator=(const TestGameState& rhs) {
        next_step_id_ = rhs.next_step_id_;
        result_ = rhs.result_;
        end_game_ = rhs.end_game_;
        return *this;
    }
};

struct TestEraseState {
    bool started_ = false;
    int winner_id_ = -1;

    MSGPACK_DEFINE_MAP(started_, winner_id_)

    TestEraseState() = default;
    TestEraseState(int winner_id) : started_(true), winner_id_(winner_id) {}
    TestEraseState(bool started, int winner_id) : started_(started), winner_id_(winner_id) {}

    TestEraseState& operator=(const TestEraseState& rhs) {
        started_ = rhs.started_;
        winner_id_ = rhs.winner_id_;
        return *this;
    }
};

struct TestDataRequest {
    int user_id_ = -1;
    int session_id_ = -1;
    TestRoute type_;
    TestAuthData data_;
    TestPoint point_;
    TestMap map_;

    MSGPACK_DEFINE_MAP(user_id_, session_id_, type_, data_, point_, map_)

    TestDataRequest() = default;
    TestDataRequest(const TestAuthData& data, TestRoute type) : type_(type), data_(data) {}
};

struct TestDataResponse {
    int user_id_ = -1;
    int session_id_ = -1;
    TestRoute type_;
    TestPoint point_;
    TestGameState game_state_;
    TestEraseState erase_state_;

    TestError error_ = TestError::Success;

    MSGPACK_DEFINE_MAP(user_id_, session_id_, type_, point_, game_state_, erase_state_, error_)

    TestDataResponse() = default;
};

}  // namespace data
}  // namespace utils
}  // namespace seabattle

MSGPACK_ADD_ENUM(seabattle::utils::data::TestRoute);
MSGPACK_ADD_ENUM(seabattle::utils::data::TestError);
MSGPACK_ADD_ENUM(seabattle::utils::data::TestResult);

#endif  // SEABATTLE_SBUTILS_DATA_TEST_DATA_H_
