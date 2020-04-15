#ifndef PROJECT_SERVER_USER_H
#define PROJECT_SERVER_USER_H
#include <string>
#include <memory>

#include "IUser.h"

class User: public IUser {
public:
    User(std::string username, int sock): IUser(std::move(username), sock){}
    int send_message(std::string message) override;
    int recieve_message(std::string message) override;
};

using UserPtr = std::shared_ptr<User>;

#endif //PROJECT_SERVER_USER_H
