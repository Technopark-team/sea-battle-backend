#include <iostream>
#include "sbcli/config/config.h"
#include "sbcli/core/game_client.h"

// TODO: добавить логгер

/*
 *   0  1  2  3  4  5  6  7  8  9
 *  ┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼
 * 0│  │  │  │  │  │  │  │  │  │  │
 *  ┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼
 * 1│  │1▓│1▓│1▓│1▓│  │  │  │  │  │
 *  ┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼
 * 2│  │  │  │  │  │  │  │  │  │  │
 *  ┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼
 * 3│  │1▓│1▓│1▓│  │2▓│2▓│2▓│  │  │
 *  ┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼
 * 4│  │  │  │  │  │  │  │  │  │1▓│
 *  ┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼
 * 5│  │  │4▓│  │  │  │  │  │  │1▓│
 *  ┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼
 * 6│  │  │  │  │  │  │  │  │  │  │
 *  ┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼
 * 7│  │  │3▓│  │  │  │  │  │  │2▓│
 *  ┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼
 * 8│  │  │  │  │  │  │  │  │  │2▓│
 *  ┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼
 * 9│  │  │2▓│  │1▓│  │3▓│3▓│  │  │
 *  ┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼
 */

size_t InitDebugMap(seabattle::utils::data::TestMap &debug_map) {
    seabattle::utils::data::TestShip point;

    point.start_.x_ = 1;
    point.start_.y_ = 1;
    point.end_.x_ = 4;
    point.end_.y_ = 1;
    debug_map.ships.insert({0, point});

    point.start_.x_ = 1;
    point.start_.y_ = 3;
    point.end_.x_ = 3;
    point.end_.y_ = 3;
    debug_map.ships.insert({1, point});

    point.start_.x_ = 5;
    point.start_.y_ = 3;
    point.end_.x_ = 7;
    point.end_.y_ = 3;
    debug_map.ships.insert({2, point});

    point.start_.x_ = 9;
    point.start_.y_ = 4;
    point.end_.x_ = 9;
    point.end_.y_ = 5;
    debug_map.ships.insert({3, point});

    point.start_.x_ = 9;
    point.start_.y_ = 7;
    point.end_.x_ = 9;
    point.end_.y_ = 8;
    debug_map.ships.insert({4, point});

    point.start_.x_ = 6;
    point.start_.y_ = 9;
    point.end_.x_ = 7;
    point.end_.y_ = 9;
    debug_map.ships.insert({5, point});

    point.start_.x_ = 4;
    point.start_.y_ = 9;
    point.end_.x_ = 4;
    point.end_.y_ = 9;
    debug_map.ships.insert({6, point});

    point.start_.x_ = 2;
    point.start_.y_ = 9;
    point.end_.x_ = 2;
    point.end_.y_ = 9;
    debug_map.ships.insert({7, point});

    point.start_.x_ = 2;
    point.start_.y_ = 7;
    point.end_.x_ = 2;
    point.end_.y_ = 7;
    debug_map.ships.insert({8, point});

    point.start_.x_ = 2;
    point.start_.y_ = 5;
    point.end_.x_ = 2;
    point.end_.y_ = 5;
    debug_map.ships.insert({9, point});
}

size_t InitConsoleSize() {
    // https://stackoverflow.com/a/42172616
    std::cout << "\e[8;45;155t";
}

/**
 * @brief Entry point
 *
 * Execution of the program
 * starts here.
 *
 * @return Program exit status
 */

int main(int argc, char *argv[]) {
    InitConsoleSize();

    seabattle::client::config::Debug debug;
    seabattle::client::config::DevMode mode;
    seabattle::client::config::User_n user_n;
    seabattle::utils::data::TestMap debug_map;

    if (!strcmp(argv[1], "debug")) {
        if (!strcmp(argv[2], "user1")) {
            user_n = seabattle::client::config::User_n::USER1;
        }
        if (!strcmp(argv[2], "user2")) {
            user_n = seabattle::client::config::User_n::USER2;
        }

        InitDebugMap(debug.debug_map);
        mode = seabattle::client::config::DevMode::DEV;

        debug.user_n = user_n;

        debug.auth_data.login_ = argv[3];
        debug.auth_data.password_ = argv[4];
    }
    if (!strcmp(argv[1], "release")) {
        mode = seabattle::client::config::DevMode::RELEASE;
    }

    debug.dev_mode = mode;

    seabattle::client::config::IpPort net_config("127.0.0.1", 2000);

    std::unique_ptr<seabattle::client::game::GameClient> client(
        new seabattle::client::game::GameClient(net_config, debug));
    client->Run();
    return 0;
}