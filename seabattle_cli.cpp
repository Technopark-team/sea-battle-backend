#include <iostream>
#include "sbcli/core/game_client.h"
#include "sbcli/config/config.h"

// TODO: добавить логгер

/**
 * @brief Entry point
 *
 * Execution of the program
 * starts here.
 *
 * @return Program exit status
 */

int main(int argc, char *argv[]) {



// https://stackoverflow.com/a/42172616
std::cout << "\e[8;45;155t";
    seabattle::client::config::Debug debug;
    seabattle::client::config::DevMode mode;
    seabattle::client::config::User_n user_n;
    if (!strcmp(argv[1], "debug")) {
        mode = seabattle::client::config::DevMode::DEV;

        if (!strcmp(argv[2], "user1")) {
            user_n = seabattle::client::config::User_n::USER1;
        }
        if (!strcmp(argv[2], "user2")) {
            user_n = seabattle::client::config::User_n::USER2;
        }
        debug.auth_data.login_ = argv[3];
        debug.auth_data.password_ = argv[4];

        debug.dev_mode = mode;
        debug.user_n = user_n;

    }
    if (!strcmp(argv[1], "release")) {
        mode = seabattle::client::config::DevMode::RELEASE;

    }




    seabattle::client::config::IpPort net_config;

    seabattle::utils::data::TestShip point;

    point.start_.x_ = 0;
    point.start_.y_ = 0;
    point.end_.x_ = 3;
    point.end_.y_ = 0;
    debug.debug_map.ships.insert({0, point});

    point.start_.x_ = 5;
    point.start_.y_ = 0;
    point.end_.x_ = 7;
    point.end_.y_ = 0;
    debug.debug_map.ships.insert({1, point});

    point.start_.x_ = 9;
    point.start_.y_ = 0;
    point.end_.x_ = 9;
    point.end_.y_ = 2;
    debug.debug_map.ships.insert({2, point});

    point.start_.x_ = 9;
    point.start_.y_ = 4;
    point.end_.x_ = 9;
    point.end_.y_ = 5;
    debug.debug_map.ships.insert({3, point});

    point.start_.x_ = 9;
    point.start_.y_ = 7;
    point.end_.x_ = 9;
    point.end_.y_ = 8;
    debug.debug_map.ships.insert({4, point});

    point.start_.x_ = 6;
    point.start_.y_ = 9;
    point.end_.x_ = 7;
    point.end_.y_ = 9;
    debug.debug_map.ships.insert({5, point});

    point.start_.x_ = 4;
    point.start_.y_ = 9;
    point.end_.x_ = 4;
    point.end_.y_ = 9;
    debug.debug_map.ships.insert({6, point});

    point.start_.x_ = 2;
    point.start_.y_ = 9;
    point.end_.x_ = 2;
    point.end_.y_ = 9;
    debug.debug_map.ships.insert({7, point});

    point.start_.x_ = 0;
    point.start_.y_ = 9;
    point.end_.x_ = 0;
    point.end_.y_ = 9;
    debug.debug_map.ships.insert({8, point});

    point.start_.x_ = 0;
    point.start_.y_ = 7;
    point.end_.x_ = 0;
    point.end_.y_ = 7;
    debug.debug_map.ships.insert({9, point});


std::unique_ptr<seabattle::client::game::GameClient> client(
    new seabattle::client::game::GameClient(net_config, debug));
client->run();
return 0;
}