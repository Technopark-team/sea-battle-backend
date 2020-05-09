#include <sys/poll.h>
#include <iostream>
#include "Engine.h"


int Engine::get_users_with_events(std::vector<Event> users_events, std::queue<Event> all_users) {
    return 0;
}

void Engine::ManageClients(std::vector<Event>& wantReadEvents, std::queue<Event>& workEvents, std::mutex& mWantReadEvents, std::mutex& mWorkEvents) {

    while(true) {
        if (wantReadEvents.empty()) {
            sleep (1);
            continue;
        }

        struct pollfd fds[1024];
        std::vector<ClientSocket> disconnected;

        int i = 0;
        for (auto& client: wantReadEvents) {
            fds[i].fd = client.client->getFd();
            fds[i].events = POLLIN;
            fds[i].revents = 0;
            ++i;
        }

        int result = poll(fds, wantReadEvents.size(), 50);

        if (result == 0) {
            //std::cout << " poll" << std::endl;
            sleep (1);
            continue;
        }

        if (result == -1) {
            std:: cout << " -1 " << std::endl;
            return;
        }

        size_t size = wantReadEvents.size();

        for (size_t k = 0; k < size; k++) {
            if (fds[k].revents == 0) {

                continue;
            }

            if (fds[k].revents & POLLHUP) {
                sleep(1);
                std::cout << "pollhup" << std::endl;
            } else if (fds[k].revents & POLLIN) {
                if (wantReadEvents[k]._status == event::WantWrite) {
                    sleep(1);
                    continue;
                }
                {
                    std::unique_lock<std::mutex> lockW(mWorkEvents);
                    workEvents.push(wantReadEvents[k]);
                }
                {
                    std::unique_lock<std::mutex> lockE(mWantReadEvents);
                    wantReadEvents.erase(wantReadEvents.begin() + k);

                    //std::cout<< "wantReadsize = " << wantReadEvents.size() << std::endl;
                }
            } else if (fds[k].revents & POLLNVAL) {
                std::cout << "pollnval" << std::endl;
            }

        }

        // delete
    }

}






