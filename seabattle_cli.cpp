#include <iostream>
#include "sbcli/core/game_client.h"

// TODO: добавить логгер

/**
 * @brief Entry point
 *
 * Execution of the program
 * starts here.
 *
 * @return Program exit status
 */

int main() {
    std::unique_ptr<seabattle::client::game::GameClient> client(
        new seabattle::client::game::GameClient());
    client->run();
    return 0;
}