#include <iostream>
#include "sbcli/core/game_client.h"

int main() {
    std::unique_ptr<seabattle::client::game::GameClient> client(
        new seabattle::client::game::GameClient());
    client->run();
    return 0;
}