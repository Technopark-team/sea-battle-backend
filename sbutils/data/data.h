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

enum GameModes {
    SINGLE = 1,
    LOAD,
    MULTI,
};

struct UserData {
    size_t user_id = -1;

    MSGPACK_DEFINE_MAP(user_id);

    UserData() = default;
    UserData(size_t id) : user_id(id) {}
};

struct AuthData {
    std::string login{};
    std::string password{};

    MSGPACK_DEFINE_MAP(login, password);

    AuthData() = default;
    AuthData(std::string log, std::string pass)
        : login(std::move(log)), password(std::move(password)) {}
};

struct Coordinate {
    size_t x = -1;
    size_t y = -1;

    MSGPACK_DEFINE_MAP(x, y);

    Coordinate() = default;
    Coordinate(size_t coord_x, size_t coord_y) : x(coord_x), y(coord_y) {}
};

struct ShipsCoordinates {
    Coordinate begin_coordinate = Coordinate();
    Coordinate end_coordinate = Coordinate();

    MSGPACK_DEFINE_MAP(begin_coordinate, end_coordinate);

    ShipsCoordinates() = default;
    ShipsCoordinates(Coordinate begin_coord, Coordinate end_coord)
        : begin_coordinate(begin_coord), end_coordinate(end_coord) {}
};

struct PlayerMap {
    std::map<std::string, ShipsCoordinates> ships = {
        {"ship4", ShipsCoordinates()},   {"ship3_1", ShipsCoordinates()},
        {"ship3_2", ShipsCoordinates()}, {"ship2_1", ShipsCoordinates()},
        {"ship2_2", ShipsCoordinates()}, {"ship2_3", ShipsCoordinates()},
        {"ship1_1", ShipsCoordinates()}, {"ship1_2", ShipsCoordinates()},
        {"ship1_3", ShipsCoordinates()}, {"ship1_4", ShipsCoordinates()},
    };

    MSGPACK_DEFINE_MAP(ships);

    PlayerMap() = default;
    PlayerMap(std::map<std::string, ShipsCoordinates> ships) : ships(ships) {}
};

struct PlayerMapToStart {
    UserData user_id = UserData();
    size_t player_mode = -1;
    PlayerMap user_map = PlayerMap();

    MSGPACK_DEFINE_MAP(user_id, player_mode, user_map);

    PlayerMapToStart() = default;
    PlayerMapToStart(UserData id, size_t mode, PlayerMap ships)
        : user_id(id), player_mode(mode), user_map(ships) {}
};

struct UserStep {
    UserData user_id = UserData();
    Coordinate step = Coordinate();

    MSGPACK_DEFINE_MAP(user_id, step);

    UserStep() = default;
    UserStep(UserData id, Coordinate coord) : user_id(id), step(coord) {}
};

struct DataRequest {
    size_t route = -1;
    UserData user_id = UserData();
    size_t game_id = -1;
    AuthData auth_data = AuthData();
    PlayerMapToStart player_map = PlayerMapToStart();
    UserStep user_step = UserStep();

    MSGPACK_DEFINE_MAP(route, user_id, game_id, auth_data, player_map, user_step);

    DataRequest() = default;
    DataRequest(size_t route, UserData user_id, size_t game_id, AuthData auth_data,
                PlayerMapToStart player_map, UserStep user_step)
        : route(route),
          user_id(user_id),
          game_id(game_id),
          auth_data(auth_data),
          player_map(player_map),
          user_step(user_step) {}
};

struct UserSessionStatus {
    std::string status_game_id{};
    std::string status_play_user{};

    MSGPACK_DEFINE_MAP(status_game_id, status_play_user);

    UserSessionStatus() = default;
    UserSessionStatus(std::string status_game_id, std::string status_play_user)
        : status_game_id(std::move(status_game_id)),
          status_play_user(std::move(status_play_user)) {}
};

struct PlayerStateMap {
    std::vector<std::string> killed_ships{};
    std::vector<Coordinate> strick_points{};
    std::vector<Coordinate> past_points{};

    MSGPACK_DEFINE_MAP(killed_ships, strick_points, past_points);

    PlayerStateMap() = default;
    PlayerStateMap(std::vector<std::string> killed_ships, std::vector<Coordinate> strick_points,
                   std::vector<Coordinate> past_points)
        : killed_ships(std::move(killed_ships)),
          strick_points(std::move(strick_points)),
          past_points(std::move(past_points)) {}
};

struct LoadGameStatus {
    PlayerMap user_map = PlayerMap();
    PlayerMap enemy_killed_map = PlayerMap();
    PlayerStateMap user_map_state = PlayerStateMap();
    PlayerStateMap enemy_map_state = PlayerStateMap();

    MSGPACK_DEFINE_MAP(user_map, enemy_killed_map, user_map_state, enemy_map_state);

    LoadGameStatus() = default;
    LoadGameStatus(PlayerMap user_map, PlayerMap enemy_killed_map, PlayerStateMap user_map_state,
                   PlayerStateMap enemy_map_state)
        : user_map(user_map),
          enemy_killed_map(enemy_killed_map),
          user_map_state(user_map_state),
          enemy_map_state(enemy_map_state) {}
};

struct GameStepStatus {
    std::string made_step{};
    Coordinate step = Coordinate();
    std::string past{};
    std::string strick{};
    std::string kill{};
    std::string may_go{};
    std::string killed_ship{};
    std::string stop_game{};
    std::string end_game{};

    MSGPACK_DEFINE_MAP(made_step, step, past, strick, kill, may_go, killed_ship, stop_game, end_game);

    GameStepStatus() = default;
    GameStepStatus(std::string made_step, Coordinate step, std::string past, std::string strick,
                   std::string kill, std::string may_go, std::string killed_ship,
                   std::string stop_game, std::string end_game)
        : made_step(made_step),
          step(step),
          past(past),
          strick(strick),
          kill(kill),
          may_go(may_go),
          killed_ship(killed_ship),
          stop_game(stop_game),
          end_game(end_game) {}
};

struct DataResponse {
    size_t route = -1;
    UserData user_data = UserData();
    std::vector<size_t> all_games_id{};
    LoadGameStatus load_game_status = LoadGameStatus();
    GameStepStatus step_status = GameStepStatus();
    UserSessionStatus user_session_status = UserSessionStatus();

    MSGPACK_DEFINE_MAP(route, user_data, all_games_id, load_game_status, step_status, user_session_status);

    DataResponse() = default;
    DataResponse(size_t route, UserData user_data, std::vector<size_t> all_games_id, LoadGameStatus load_game_status,
                 GameStepStatus step_status, UserSessionStatus user_session_status)
        : route(route),
          user_data(user_data),
          all_games_id(std::move(all_games_id)),
          load_game_status(load_game_status),
          step_status(step_status),
          user_session_status(user_session_status) {}
};

}  // namespace data
}  // namespace utils
}  // namespace seabattle

#endif  // SEABATTLE_DATA_H
