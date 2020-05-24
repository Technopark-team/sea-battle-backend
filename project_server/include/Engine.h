#ifndef PROJECT_SERVER_ENGINE_H
#define PROJECT_SERVER_ENGINE_H

#include <utility>

#include "IEngine.h"


class Engine: public IEngine {
private:
    std::mutex mNeedDelete;
public:
    Engine(): IEngine() {}
    void ManageClients(std::vector<Event>& wantReadEvents, std::queue<Event>& workEvents,
            std::mutex& mWantReadEvents, std::mutex& mWorkEvents) override;
    void deleteEvents(std::vector<Event>& wantReadEvents, std::vector<size_t>& needDelete, std::mutex& mWantReadEvents);
};


#endif //PROJECT_SERVER_ENGINE_H
