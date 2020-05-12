#include <sys/poll.h>
#include <iostream>

#include "Engine.h"



void Engine::deleteEvents(std::vector<Event>& wantReadEvents, std::vector<size_t>& needDelete, std::mutex& mWantReadEvents) {
    {
        std::unique_lock<std::mutex> lock(mWantReadEvents);
        //std::cout << "before: " << wantReadEvents.size() << " need delete size " << needDelete.size() << std::endl;
        for (auto& id: needDelete) {
            wantReadEvents.erase(std::remove_if(wantReadEvents.begin(), wantReadEvents.end(), [&id](Event& event){return event.id == id;}), wantReadEvents.end());
        }

    }
    {
        std::unique_lock<std::mutex> lock(mNeedDelete);
        needDelete.clear();
    }
    //std::cout << "after: " << wantReadEvents.size() << " need delete size " << needDelete.size() << std::endl;
}

void Engine::ManageClients(std::vector<Event>& wantReadEvents, std::queue<Event>& workEvents, std::mutex& mWantReadEvents, std::mutex& mWorkEvents) {

    while(true) {
        if (wantReadEvents.empty()) {
            usleep (1000);
            continue;
        }
        struct pollfd fds[1024];
        std::vector<size_t> needDelete;

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
            usleep (1000);
            continue;
        }

        if (result == -1) {
            std:: cerr << " poll failed" << std::endl;
            return;
        }

        size_t size = wantReadEvents.size();

        for (size_t k = 0; k < size; k++) {
            if (fds[k].revents == 0) {
                continue;
            }

            if (fds[k].revents & POLLHUP) {
                std::unique_lock<std::mutex> lockN(mNeedDelete);
                needDelete.push_back(wantReadEvents[k].id);
                //std::cout << "pollhup" << std::endl;
            } else if (fds[k].revents & POLLIN) {
                if (wantReadEvents[k]._status == event::WantWrite) {
                    continue;
                }
                {
                    std::unique_lock<std::mutex> lockW(mWorkEvents);
                    workEvents.push(wantReadEvents[k]);
                }
                {
                    std::unique_lock<std::mutex> lockN(mNeedDelete);
                    needDelete.push_back(wantReadEvents[k].id);
                }
            } else if (fds[k].revents & POLLNVAL) {
                std::unique_lock<std::mutex> lockN(mNeedDelete);
                needDelete.push_back(wantReadEvents[k].id);
                //std::cout << "pollnval" << std::endl;
            }
        }
        deleteEvents(wantReadEvents, needDelete, mWantReadEvents);
        usleep(1000);
    }
}






