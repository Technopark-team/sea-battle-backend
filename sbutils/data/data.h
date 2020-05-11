#ifndef SEABATTLE_DATA_H
#define SEABATTLE_DATA_H

#include <map>
#include <string>
#include <vector>

namespace seabattle {
namespace utils {
namespace data {

// TODO: [ВАЖНО!] добавить документацию к методам и свойствам

enum Routes {
    GET_GAME_ALL,
    GET_GAME_OPEN,
    GET_GAME_STEP,
    GET_GAME_STATE,

    POST_SIGN_IN,
    POST_SIGN_UP,
    POST_GAME_START,
    POST_GAME_STEP,

    PUT_GAME_SAVE,
    PUT_GAME_STOP
};

struct AuthData {
    std::string login{};
    std::string password{};

    AuthData() = default;
    AuthData(std::string log, std::string pass)
        : login(std::move(log)), password(std::move(password)) {}
};

struct Coordinate {
    char x = -1;
    char y = -1;

    Coordinate() = default;
    Coordinate(char coord_x, char coord_y) : x(coord_x), y(coord_y) {}
};

struct ShipsCoordinates {
    Coordinate begin_coordinate = Coordinate();
    Coordinate end_coordinate = Coordinate();

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

    PlayerMap() = default;
    PlayerMap(std::map<std::string, ShipsCoordinates> ships) : ships(ships) {}
};

struct PlayerMapToStart {
    size_t user_id = 0;
    std::string player_mode{};
    PlayerMap user_map = PlayerMap();

    PlayerMapToStart() = default;
    PlayerMapToStart(size_t id, std::string mode, PlayerMap ships)
        : user_id(id), player_mode(std::move(mode)), ships(ships) {}
};

struct UserStep {
    size_t user_id = 0;
    Coordinate step = Coordinate();

    UserStep() = default;
    UserStep(size_t id, Coordinate coord) : user_id(id), step(coord) {}
};

struct DataRequest {
    size_t route = -1;
    size_t user_id = 0;
    size_t game_id = 0;
    AuthData auth_data = AuthData();
    PlayerMapToStart player_map = PlayerMapToStart();
    UserStep user_step = UserStep();
    //    GameStepStatus step_status = GameStepStatus(); //

    DataRequest() = default;
    DataRequest(size_t route, size_t user_id, size_t game_id, AuthData auth_data,
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

    UserSessionStatus() = default;
    UserSessionStatus(std::string status_game_id, std::string status_play_user)
        : status_game_id(std::move(status_game_id)),
          status_play_user(std::move(status_play_user)) {}
};

struct PlayerStateMap {
    std::vector<std::string> killed_ships{};
    std::vector<Coordinate> strick_points{};
    std::vector<Coordinate> past_points{};

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
    std::vector<size_t> all_games_id{};
    LoadGameStatus load_game_status = LoadGameStatus();
    GameStepStatus step_status = GameStepStatus();
    UserSessionStatus user_session_status = UserSessionStatus();

    DataResponse() = default;
    DataResponse(size_t route, std::vector<size_t> all_games_id, LoadGameStatus load_game_status,
                 GameStepStatus step_status, UserSessionStatus user_session_status)
        : route(route),
          all_games_id(std::move(all_games_id)),
          load_game_status(load_game_status),
          step_status(step_status),
          user_session_status(user_session_status) {}
};

}  // namespace data
}  // namespace utils
}  // namespace sbutils

#endif  // SEABATTLE_DATA_H
