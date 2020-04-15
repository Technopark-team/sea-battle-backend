#ifndef PROJECT_SERVER_IENGINE_H
#define PROJECT_SERVER_IENGINE_H
#include <vector>

#include "User.h"

class IEngine {
public:
    IEngine(){}
    virtual void ManageClients() = 0;
    virtual ~IEngine() = default;
};


#endif //PROJECT_SERVER_IENGINE_H
