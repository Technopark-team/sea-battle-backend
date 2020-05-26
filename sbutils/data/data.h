#ifndef SEABATTLE_DATA_H
#define SEABATTLE_DATA_H

#include <map>
#include <msgpack.hpp>
#include <string>
#include <vector>

namespace seabattle {
namespace utils {
namespace data {

/**
 * @brief Routes is an enumeration describes HTTP-like request type&route for TCP connection.
 *
 * There is 3 prefixes: GET, POST, PUT - similar HTTP likehood notation.
 * There is 2 main blocks: GAME, SIGN - first is related to Game model, second - User model.
 */
enum class Routes {
    DEFAULT = -1,
    GET_GAME_ALL = 1,
    GET_GAME_OPEN,
    GET_GAME_STEP,
    GET_GAME_STATE,

    POST_SIGN_IN,
    POST_SIGN_UP,
    POST_GAME_START,
    POST_GAME_STEP,

    PUT_GAME_SAVE,
    PUT_GAME_STOP,
};

/**
 * @brief GameModes is an enumeration describes usual game modes.
 */
enum class GameModes {
    DEFAULT = -1,
    SINGLE_MODE = 1,
    LOAD_MODE,
    MULTI_MODE,
};

/**
 * @brief ShipType is an enumeration describes possible ships which can be placed around the map
 * cells.
 */
enum class ShipType {
    DEFAULT = -1,
    SHIP4 = 1,
    SHIP3_1,
    SHIP3_2,
    SHIP2_1,
    SHIP2_2,
    SHIP2_3,
    SHIP1_1,
    SHIP1_2,
    SHIP1_3,
    SHIP1_4,
};

/**
 * @brief GameStatus is an enumeration describes current game session status (started or not,
 * client/enemy exit the game, client/enemy win/lose the game).
 */
enum class GameStatusCode {
    DEFAULT = -1,
    GAME_START = 1,
    GAME_WAIT,
    GAME_STOP, /**<Game has ended because someone exit the game. */
    GAME_END,  /**<Game has ended because someone has killed all ships in the game. */
};

/**
 * @brief WinStatus is an enumeration describes current game win status (user win or lose the game).
 */
enum class WinStatus {
    DEFAULT = -1,
    WIN = 1,
    LOSE,
};

/**
 * @brief PlayStatus is an enumeration describes current game session status (who is making a step).
 */
enum class PlayStatus {
    DEFAULT = -1,
    PLAY_GO = 1,
    PLAY_WAIT,
};

/**
 * @brief YesNo is an enumeration describes yes and no types as codes.
 */
enum class YesNo {
    DEFAULT = -1,
    YES = 1,
    NO,
};

/**
 * @brief Error describes error codes from server.
 */
enum class Error {
    DEFAULT = -1,
    SUCCESS = 0,
    NOTFOUND,
    FULL,
    USEREXIST,
    INVALIDLOGIN,
    STARTED,
    WAIT,
    NOTVALIDMAP,
    ENDGAME,
};

/**
 * @brief Result is a enum class to describe result of user step in game.
 */
enum class Result {
    DEFAULT = -1,
    MISS = 0,
    HIT,
    KILL,
    BADPOINT,
};

/**
 * @brief UserData is a struct stores user ID in DataBase.
 *
 * It is a base part of main DataRequest struct. By architecture its role is Cookie as well.
 */
struct UserData {
    size_t user_id = -1;

    MSGPACK_DEFINE_MAP(
        user_id); /**< Define MSGPACK adaptor for custom struct for further serialization. */

    UserData() = default;
    UserData(size_t id) : user_id(id) {}
};

/**
 * @brief GameData is a struct stores current game session ID and enemy's data on server and in DB.
 *
 * It is a base part of main DataRequest struct.
 */
struct GameData {
    size_t game_id = -1;
    UserData enemy_id = UserData();

    MSGPACK_DEFINE_MAP(
        game_id,
        enemy_id); /**< Define MSGPACK adaptor for custom struct for further serialization. */

    GameData() = default;
    GameData(size_t id, UserData enemy) : game_id(id), enemy_id(std::move(enemy)) {}
};

/**
 * @brief AuthData is a struct stores client's login and password data.
 *
 * It is a base part of main DataRequest struct.
 */
struct AuthData {
    std::string login{};
    std::string password{};

    MSGPACK_DEFINE_MAP(
        login,
        password); /**< Define MSGPACK adaptor for custom struct for further serialization. */

    AuthData() = default;
    AuthData(std::string log, std::string pass)
        : login(std::move(log)), password(std::move(password)) {}
};

/**
 * @brief Coordinate is a struct stores X & Y coordinates for ship's location or for user's step.
 */
struct Coordinate {
    size_t x = -1;
    size_t y = -1;

    MSGPACK_DEFINE_MAP(
        x, y); /**< Define MSGPACK adaptor for custom struct for further serialization. */

    Coordinate() = default;
    Coordinate(size_t coord_x, size_t coord_y) : x(coord_x), y(coord_y) {}
};

/**
 * @brief ShipCoordinates is a struct stores begin & end Coordinate structs of any ship.
 */
struct ShipCoordinates {
    Coordinate begin_coordinate = Coordinate();
    Coordinate end_coordinate = Coordinate();

    MSGPACK_DEFINE_MAP(
        begin_coordinate,
        end_coordinate); /**< Define MSGPACK adaptor for custom struct for further serialization. */

    ShipCoordinates() = default;
    ShipCoordinates(Coordinate begin_coord, Coordinate end_coord)
        : begin_coordinate(begin_coord), end_coordinate(end_coord) {}
};

/**
 * @brief PlayerMap is a struct stores pairs: ship type ID and its ShipCoordinates.
 */
struct PlayerMap {
    std::map<ShipType, ShipCoordinates> ships = {
        {ShipType::SHIP4, ShipCoordinates()},   {ShipType::SHIP3_1, ShipCoordinates()},
        {ShipType::SHIP3_2, ShipCoordinates()}, {ShipType::SHIP2_1, ShipCoordinates()},
        {ShipType::SHIP2_2, ShipCoordinates()}, {ShipType::SHIP2_3, ShipCoordinates()},
        {ShipType::SHIP1_1, ShipCoordinates()}, {ShipType::SHIP1_2, ShipCoordinates()},
        {ShipType::SHIP1_3, ShipCoordinates()}, {ShipType::SHIP1_4, ShipCoordinates()},
    };

    MSGPACK_DEFINE_MAP(
        ships); /**< Define MSGPACK adaptor for custom struct for further serialization. */

    PlayerMap() = default;
    PlayerMap(std::map<ShipType, ShipCoordinates> ships) : ships(std::move(ships)) {}
};

/**
 * @brief PlayerMapToStart is a struct stores game mode type ID and client's own ship map to play.
 *
 * It is a base part of main DataRequest struct.
 */
struct PlayerMapToStart {
    GameModes player_mode = GameModes::DEFAULT;
    PlayerMap user_map = PlayerMap();

    MSGPACK_DEFINE_MAP(
        player_mode,
        user_map); /**< Define MSGPACK adaptor for custom struct for further serialization. */

    PlayerMapToStart() = default;
    PlayerMapToStart(GameModes mode, PlayerMap ships)
        : player_mode(std::move(mode)), user_map(std::move(ships)) {}
};

/**
 * @brief UserStep is a struct stores client's step Coordinate struct.
 *
 * It is a base part of main DataRequest struct.
 */
struct UserStep {
    Coordinate step = Coordinate();

    MSGPACK_DEFINE_MAP(
        step); /**< Define MSGPACK adaptor for custom struct for further serialization. */

    UserStep() = default;
    UserStep(Coordinate coord) : step(std::move(coord)) {}
};

/**
 * @brief DataRequest is a struct sent by client as client's request.
 *
 * Each field is initialized depends on client's request type.
 * Some fields will be sent with default values which are not needed for the server.
 * Other fields will be send with actual data.
 * Brief description for each field is documented above.
 */
struct DataRequest {
    Routes route = Routes::DEFAULT;
    UserData user_data = UserData();
    GameData game_data = GameData();
    AuthData auth_data = AuthData();
    PlayerMapToStart player_map = PlayerMapToStart();
    UserStep user_step = UserStep();

    MSGPACK_DEFINE_MAP(
        route, user_data, game_data, auth_data, player_map,
        user_step); /**< Define MSGPACK adaptor for custom struct for further serialization. */

    DataRequest() = default;
    DataRequest(Routes route, UserData user_data, GameData game_data, AuthData auth_data,
                PlayerMapToStart player_map, UserStep user_step)
        : route(std::move(route)),
          user_data(std::move(user_data)),
          game_data(std::move(game_data)),
          auth_data(std::move(auth_data)),
          player_map(std::move(player_map)),
          user_step(std::move(user_step)) {}
};

/**
 * @brief GameSessionStatus is a struct describes 2 aspects of current game session.
 *
 * It is a base part of main DataResponse struct.
 */
struct GameSessionStatus {
    GameStatusCode game_status = GameStatusCode::DEFAULT;
    PlayStatus play_status = PlayStatus::DEFAULT;

    MSGPACK_DEFINE_MAP(
        game_status,
        play_status); /**< Define MSGPACK adaptor for custom struct for further serialization. */

    GameSessionStatus() = default;
    GameSessionStatus(GameStatusCode game_status, PlayStatus play_status)
        : game_status(std::move(game_status)), play_status(std::move(play_status)) {}
};

/**
 * @brief PlayerStateMap is a struct describes client or bot exact game session backup for Load
 * play.
 */
struct PlayerStateMap {
    PlayerMap player_map = PlayerMap();
    std::vector<ShipType> killed_ships{};    /**< List of killed ship types. */
    std::vector<Coordinate> strick_points{}; /**< List of map cells marked as strick. */
    std::vector<Coordinate> past_points{}; /**< List of map cells marked as past (rus. мимо). */

    MSGPACK_DEFINE_MAP(
        killed_ships, strick_points,
        past_points); /**< Define MSGPACK adaptor for custom struct for further serialization. */

    PlayerStateMap() = default;
    PlayerStateMap(std::vector<ShipType> killed_ships, std::vector<Coordinate> strick_points,
                   std::vector<Coordinate> past_points)
        : killed_ships(std::move(killed_ships)),
          strick_points(std::move(strick_points)),
          past_points(std::move(past_points)) {}
};

/**
 * @brief LoadGameStatus is a struct describes client and bot game session backup for Load play.
 *
 * It is a base part of main DataResponse struct.
 */
struct LoadGameStatus {
    PlayerStateMap user_map_state = PlayerStateMap();
    PlayerStateMap enemy_map_state = PlayerStateMap();

    MSGPACK_DEFINE_MAP(user_map_state, enemy_map_state); /**< Define MSGPACK adaptor for custom
                                                            struct for further serialization. */

    LoadGameStatus() = default;
    LoadGameStatus(PlayerStateMap user_map_state, PlayerStateMap enemy_map_state)
        : user_map_state(std::move(user_map_state)), enemy_map_state(std::move(enemy_map_state)) {}
};

/**
 * @brief StepStatus is a struct describes result of client/enemy step to renew it on corresponding
 * map.
 */
struct StepStatus {
    Result user_step_result = Result::DEFAULT;
    ShipType killed_ship = ShipType::DEFAULT; /**< Killed ship type ID (if kill field has "YES"). */
    ShipCoordinates killed_coordinates =
        ShipCoordinates(); /**< Killed ship begin and coordinates (if kill field has "YES"). */

    MSGPACK_DEFINE_MAP(user_step_result, killed_ship,
                       killed_coordinates); /**< Define MSGPACK adaptor for custom struct for
                                               further serialization. */

    StepStatus() = default;
    StepStatus(Result user_step_result, ShipType killed_ship,
               ShipCoordinates killed_coordinates)
        : user_step_result(std::move(user_step_result)),
          killed_ship(std::move(killed_ship)),
          killed_coordinates(std::move(killed_coordinates)) {}
};

/**
 * @brief GameStatus is a struct describes 2 aspects of current game session.
 *
 * It is a base part of main DataResponse struct.
 * This struct is returned in response on 2 Routes requests POST_GAME_STEP and GET_GAME_STEP.
 * In case of POST_GAME_STEP server responses with the result of CLIENT step (past/strick/killed).
 * In case of GET_GAME_STEP server responses with the result of ENEMY (bot or other player in
 * current game session) step (past/strick/killed).
 */
struct GameStatus {
    YesNo made_step = YesNo::DEFAULT;      /**< Did enemy make a step? YES/NO. */
    Coordinate step = Coordinate();        /**< Enemy step. */
    UserData next_step = UserData();       /**< Whose step is next? Current client/Enemy. */
    StepStatus step_result = StepStatus(); /**< Result of step of client/enemy. */
    GameStatusCode game_status =
        GameStatusCode::DEFAULT; /**< Did enemy stop the game? GAME_STOP/GAME_END. */
    WinStatus win_status =
        WinStatus::DEFAULT; /**< Did game be ended because of someones win? WIN/LOSE. */

    MSGPACK_DEFINE_MAP(
        made_step, step, next_step, game_status,
        win_status); /**< Define MSGPACK adaptor for custom struct for further serialization. */

    GameStatus() = default;
    GameStatus(YesNo made_step, Coordinate step, UserData next_step, StepStatus step_result,
               GameStatusCode game_status, WinStatus win_status)
        : made_step(std::move(made_step)),
          step(std::move(step)),
          next_step(std::move(next_step)),
          step_result(std::move(step_result)),
          game_status(std::move(game_status)),
          win_status(std::move(win_status)) {}
};

/**
 * @brief Error is a struct returned by server if client has sent wrong data (for map or step in
 * game process).
 */
struct ResponseError {
    Error error = Error::DEFAULT;
    std::string message{};

    MSGPACK_DEFINE_MAP(error, message);

    ResponseError() = default;
    ResponseError(Error er, std::string msg) : error(std::move(er)), message(std::move(msg)) {}
};

/**
 * @brief DataResponse is a struct returned by server on each client's request.
 *
 * Each field is initialized depends on server's response type.
 * Some fields will be sent with default values which are not needed for client.
 * Other fields will be send with actual data.
 * Brief description for each field is documented above.
 */
struct DataResponse {
    Routes route = Routes::DEFAULT;
    UserData user_data = UserData();
    GameData game_id = GameData();
    std::vector<size_t> all_games_id{};
    LoadGameStatus load_game_status = LoadGameStatus();
    GameStatus step_status = GameStatus();
    GameSessionStatus user_session_status = GameSessionStatus();
    ResponseError error = ResponseError();

    MSGPACK_DEFINE_MAP(route, user_data, game_id, all_games_id, load_game_status, step_status,
                       user_session_status, error);

    DataResponse() = default;
    DataResponse(Routes route, UserData user_data, GameData game_id,
                 std::vector<size_t> all_games_id, LoadGameStatus load_game_status,
                 GameStatus step_status, GameSessionStatus user_session_status, ResponseError error)
        : route(std::move(route)),
          user_data(std::move(user_data)),
          game_id(std::move(game_id)),
          all_games_id(std::move(all_games_id)),
          load_game_status(std::move(load_game_status)),
          step_status(std::move(step_status)),
          user_session_status(std::move(user_session_status)),
          error(std::move(error)) {}
};

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

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
    Default = -1,
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

    MSGPACK_DEFINE_MAP(login_, password_);

    TestAuthData() = default;
    TestAuthData(const std::string& login, const std::string& password): login_(login), password_(password) {}
};


enum class TestResult {
    Default = -1,
    Miss = 1,
    Hit,
    Kill,
    BadPoint
};

struct TestGameState {
    int next_step_id_ = -1;
    TestResult result_ = TestResult::Default;
    bool end_game_;

    MSGPACK_DEFINE_MAP(next_step_id_, result_, end_game_);

    TestGameState() = default;
    TestGameState(int next_step_id, TestResult result, bool end_game = false): next_step_id_(next_step_id), result_(result), end_game_(end_game){}

    TestGameState& operator=(const TestGameState& rhs) {
        next_step_id_ = rhs.next_step_id_;
        result_ = rhs.result_;
        end_game_ = rhs.end_game_;
        return *this;
    }
};

struct TestPoint {
    size_t x_;
    size_t y_;

    MSGPACK_DEFINE_MAP(x_, y_);

    TestPoint(size_t x, size_t y): x_(x), y_(y){}
    TestPoint():x_(-1), y_(-1) {}

    const bool isValid() const {
        return x_ < 10 && y_ < 10;
    }
};

struct TestShip {
    TestPoint start_;
    TestPoint end_;

    MSGPACK_DEFINE_MAP(start_, end_);

    TestShip() = default;
    TestShip(size_t start_x, size_t start_y, size_t end_x, size_t end_y):start_(start_x, start_y), end_(end_x, end_y) {}
    TestShip(const TestPoint& start, const TestPoint& end): start_(start), end_(end) {}

    const bool IsValid() const {
        return (start_.x_ == end_.x_ || start_.y_ == end_.y_) && start_.isValid() && end_.isValid();
    }

    const size_t Length() const {
        return (start_.x_ == end_.x_)?(end_.y_ - start_.y_ + 1):(end_.x_ - start_.x_ + 1);
    }
};

struct TestMap {
    std::map<int, TestShip> ships;
    MSGPACK_DEFINE_MAP(ships);
    TestMap() = default;
};

struct TestEraseState {
    bool started_ = false;
    int winner_id_ = -1;

    MSGPACK_DEFINE_MAP(started_, winner_id_);

    TestEraseState() = default;
    TestEraseState(int winner_id): started_(true), winner_id_(winner_id) {}
    TestEraseState(bool started, int winner_id): started_(started), winner_id_(winner_id) {}

    TestEraseState& operator= (const TestEraseState& rhs) {
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

    MSGPACK_DEFINE_MAP(user_id_, session_id_, type_, data_, point_, map_);

    TestDataRequest() = default;
    TestDataRequest(const TestAuthData& data, TestRoute type): data_(data), type_(type) {}
};

struct TestDataResponse {
    int user_id_ = -1;
    int session_id_ = -1;

    TestRoute type_;
    TestPoint point_;
    TestGameState game_state_;
    TestEraseState erase_state_;

    TestError error_ = TestError::Default;

    MSGPACK_DEFINE_MAP(user_id_, session_id_, point_, game_state_ , erase_state_, error_);

    TestDataResponse() = default;
};

}  // namespace data
}  // namespace utils
}  // namespace seabattle

// should be in global namespace
MSGPACK_ADD_ENUM(seabattle::utils::data::Routes);
MSGPACK_ADD_ENUM(seabattle::utils::data::GameModes);
MSGPACK_ADD_ENUM(seabattle::utils::data::ShipType);
MSGPACK_ADD_ENUM(seabattle::utils::data::GameStatusCode);
MSGPACK_ADD_ENUM(seabattle::utils::data::WinStatus);
MSGPACK_ADD_ENUM(seabattle::utils::data::PlayStatus);
MSGPACK_ADD_ENUM(seabattle::utils::data::YesNo);
MSGPACK_ADD_ENUM(seabattle::utils::data::Error);
MSGPACK_ADD_ENUM(seabattle::utils::data::Result);

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

MSGPACK_ADD_ENUM(seabattle::utils::data::TestRoute);
MSGPACK_ADD_ENUM(seabattle::utils::data::TestError);
MSGPACK_ADD_ENUM(seabattle::utils::data::TestResult);

#endif  // SEABATTLE_DATA_H
