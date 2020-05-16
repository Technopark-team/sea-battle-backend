#ifndef SEABATTLE_DATA_H
#define SEABATTLE_DATA_H

#include <map>
#include <msgpack.hpp>
#include <string>
#include <vector>

namespace seabattle {
namespace utils {
namespace data {

// TODO: [ВАЖНО!] добавить документацию к методам и свойствам
// TODO: оставшиеся строковые переменные перевести на enum (да/нет, корабли)
// TODO: добавить где нужно std::move
// TODO: сделать enum class

/**
 * @brief Routes is an enumeration describes HTTP-like request type&route for TCP connection.
 *
 * There is 3 prefixes: GET, POST, PUT - similar HTTP likehood notation.
 * There is 2 main blocks: GAME, SIGN - first is related to Game model, second - User model.
 */
enum Routes {
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
enum GameModes {
    SINGLE_MODE = 1,
    LOAD_MODE,
    MULTI_MODE,
};

/**
 * @brief ShipType is an enumeration describes possible ships which can be placed around the map cells.
 */
enum ShipType {
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
 * @brief GameStatus is an enumeration describes current game session status (started or not).
 */
enum GameStatus {
    GAME_START = 1,
    GAME_WAIT,
};

/**
 * @brief PlayStatus is an enumeration describes current game session status (who is making a step).
 */
enum PlayStatus {
    PLAY_GO = 1,
    PLAY_WAIT,
};

/**
 * @brief YesNo is an enumeration describes yes and no types as codes.
 */
enum YesNo {
    YES = 1,
    NO,
};

/**
 * @brief UserData is a struct stores user ID in DataBase.
 *
 * It is a base part of main DataRequest struct. By architecture its role is Cookie as well.
 */
struct UserData {
    size_t user_id = -1;

    MSGPACK_DEFINE_MAP(user_id);    /**< Define MSGPACK adaptor for custom struct for further serialization. */

    UserData() = default;
    UserData(size_t id) : user_id(id) {}
};

/**
 * @brief GameData is a struct stores current game session ID on server and in DB.
 *
 * It is a base part of main DataRequest struct.
 */
struct GameData {
    size_t game_id = -1;

    MSGPACK_DEFINE_MAP(game_id);    /**< Define MSGPACK adaptor for custom struct for further serialization. */

    GameData() = default;
    GameData(size_t id) : game_id(id) {}
};

/**
 * @brief AuthData is a struct stores client's login and password data.
 *
 * It is a base part of main DataRequest struct.
 */
struct AuthData {
    std::string login{};
    std::string password{};

    MSGPACK_DEFINE_MAP(login, password);    /**< Define MSGPACK adaptor for custom struct for further serialization. */

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

    MSGPACK_DEFINE_MAP(x, y);    /**< Define MSGPACK adaptor for custom struct for further serialization. */

    Coordinate() = default;
    Coordinate(size_t coord_x, size_t coord_y) : x(coord_x), y(coord_y) {}
};

/**
 * @brief ShipCoordinates is a struct stores begin & end Coordinate structs of any ship.
 */
struct ShipCoordinates {
    Coordinate begin_coordinate = Coordinate();
    Coordinate end_coordinate = Coordinate();

    MSGPACK_DEFINE_MAP(begin_coordinate, end_coordinate);    /**< Define MSGPACK adaptor for custom struct for further serialization. */

    ShipCoordinates() = default;
    ShipCoordinates(Coordinate begin_coord, Coordinate end_coord)
        : begin_coordinate(begin_coord), end_coordinate(end_coord) {}
};

/**
 * @brief PlayerMap is a struct stores pairs: ship type ID and its ShipCoordinates.
 */
struct PlayerMap {
    std::map<size_t, ShipCoordinates> ships = {
        {SHIP4, ShipCoordinates()},   {SHIP3_1, ShipCoordinates()},
        {SHIP3_2, ShipCoordinates()}, {SHIP2_1, ShipCoordinates()},
        {SHIP2_2, ShipCoordinates()}, {SHIP2_3, ShipCoordinates()},
        {SHIP1_1, ShipCoordinates()}, {SHIP1_2, ShipCoordinates()},
        {SHIP1_3, ShipCoordinates()}, {SHIP1_4, ShipCoordinates()},
    };

    MSGPACK_DEFINE_MAP(ships);    /**< Define MSGPACK adaptor for custom struct for further serialization. */

    PlayerMap() = default;
    PlayerMap(std::map<size_t, ShipCoordinates> ships) : ships(std::move(ships)) {}
};

/**
 * @brief PlayerMapToStart is a struct stores game mode type ID and client's own ship map to play.
 *
 * It is a base part of main DataRequest struct.
 */
struct PlayerMapToStart {
    size_t player_mode = -1;
    PlayerMap user_map = PlayerMap();

    MSGPACK_DEFINE_MAP(player_mode, user_map);    /**< Define MSGPACK adaptor for custom struct for further serialization. */

    PlayerMapToStart() = default;
    PlayerMapToStart(size_t mode, PlayerMap ships) : player_mode(mode), user_map(std::move(ships)) {}
};

/**
 * @brief UserStep is a struct stores client's step Coordinate struct.
 *
 * It is a base part of main DataRequest struct.
 */
struct UserStep {
    Coordinate step = Coordinate();

    MSGPACK_DEFINE_MAP(step);    /**< Define MSGPACK adaptor for custom struct for further serialization. */

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
    size_t route = -1;
    UserData user_id = UserData();
    GameData game_id = GameData();
    AuthData auth_data = AuthData();
    PlayerMapToStart player_map = PlayerMapToStart();
    UserStep user_step = UserStep();

    MSGPACK_DEFINE_MAP(route, user_id, game_id, auth_data, player_map, user_step);    /**< Define MSGPACK adaptor for custom struct for further serialization. */

    DataRequest() = default;
    DataRequest(size_t route, UserData user_id, GameData game_id, AuthData auth_data,
                PlayerMapToStart player_map, UserStep user_step)
        : route(route),
          user_id(std::move(user_id)),
          game_id(std::move(game_id)),
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
    size_t status_game_id = -1;
    size_t status_play_user = -1;

    MSGPACK_DEFINE_MAP(status_game_id, status_play_user);    /**< Define MSGPACK adaptor for custom struct for further serialization. */

    GameSessionStatus() = default;
    GameSessionStatus(size_t status_game_id, size_t status_play_user)
        : status_game_id(status_game_id),
          status_play_user(status_play_user) {}
};

/**
 * @brief PlayerStateMap is a struct describes client or bot exact game session backup for Load play.
 */
struct PlayerStateMap {
    PlayerMap player_map = PlayerMap();
    std::vector<size_t> killed_ships{};           /**< List of killed ship types. */
    std::vector<Coordinate> strick_points{};      /**< List of map cells marked as strick. */
    std::vector<Coordinate> past_points{};        /**< List of map cells marked as past (rus. мимо). */

    MSGPACK_DEFINE_MAP(killed_ships, strick_points, past_points);    /**< Define MSGPACK adaptor for custom struct for further serialization. */

    PlayerStateMap() = default;
    PlayerStateMap(std::vector<size_t> killed_ships, std::vector<Coordinate> strick_points,
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

    MSGPACK_DEFINE_MAP(user_map_state, enemy_map_state);    /**< Define MSGPACK adaptor for custom struct for further serialization. */

    LoadGameStatus() = default;
    LoadGameStatus(PlayerStateMap user_map_state, PlayerStateMap enemy_map_state)
        : user_map_state(std::move(user_map_state)),
          enemy_map_state(std::move(enemy_map_state)) {}
};

/**
 * @brief GameStepStatus is a struct describes 2 aspects of current game session.
 *
 * It is a base part of main DataResponse struct.
 * This struct is returned in response on 2 Routes requests POST_GAME_STEP and GET_GAME_STEP.
 * In case of POST_GAME_STEP server responses with the result of CLIENT step (past/strick/killed).
 * In case of GET_GAME_STEP server responses with the result of ENEMY (bot or other player in current game session) step (past/strick/killed).
 */
struct GameStepStatus {
    size_t made_step = -1;                                    /**< Did enemy make a step? YES/NO. */
    Coordinate step = Coordinate();                           /**< Enemy step. */
    size_t past = -1;                                         /**< Did client/enemy past? YES/NO. */
    size_t strick = -1;                                       /**< Did client/enemy strick? YES/NO. */
    size_t kill = -1;                                         /**< Did client/enemy kill? YES/NO. */
    size_t may_go = -1;                                       /**< Can client make a step? YES/NO. */
    size_t killed_ship = -1;                                  /**< Killed ship type ID (if kill field has "YES"). */
    ShipCoordinates killed_coordinates = ShipCoordinates();   /**< Killed ship begin and coordinates (if kill field has "YES"). */
    size_t stop_game = -1;                                    /**< Did enemy stop the game? YES/NO. */
    size_t end_game = -1;                                     /**< Did game be ended because of someones win? YES/NO. */

    MSGPACK_DEFINE_MAP(made_step, step, past, strick, kill, may_go, killed_ship, killed_coordinates, stop_game, end_game);    /**< Define MSGPACK adaptor for custom struct for further serialization. */

    GameStepStatus() = default;
    GameStepStatus(size_t made_step, Coordinate step, size_t past, size_t strick,
                   size_t kill, size_t may_go, size_t killed_ship, ShipCoordinates killed_coordinates,
                   size_t stop_game, size_t end_game)
        : made_step(made_step),
          step(std::move(step)),
          past(past),
          strick(strick),
          kill(kill),
          may_go(may_go),
          killed_ship(killed_ship),
          killed_coordinates(std::move(killed_coordinates)),
          stop_game(stop_game),
          end_game(end_game) {}
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
    size_t route = -1;
    UserData user_data = UserData();
    GameData game_id = GameData();
    std::vector<size_t> all_games_id{};
    LoadGameStatus load_game_status = LoadGameStatus();
    GameStepStatus step_status = GameStepStatus();
    GameSessionStatus user_session_status = GameSessionStatus();

    MSGPACK_DEFINE_MAP(route, user_data, game_id, all_games_id, load_game_status, step_status, user_session_status);

    DataResponse() = default;
    DataResponse(size_t route, UserData user_data, GameData game_id, std::vector<size_t> all_games_id, LoadGameStatus load_game_status,
                 GameStepStatus step_status, GameSessionStatus user_session_status)
        : route(route),
          user_data(std::move(user_data)),
          game_id(std::move(game_id)),
          all_games_id(std::move(all_games_id)),
          load_game_status(std::move(load_game_status)),
          step_status(std::move(step_status)),
          user_session_status(std::move(user_session_status)) {}
};

}  // namespace data
}  // namespace utils
}  // namespace seabattle

#endif  // SEABATTLE_DATA_H
