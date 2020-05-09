#ifndef PROJECT_SERVER_USER_H
#define PROJECT_SERVER_USER_H

#include <string>
#include <memory>
#include <functional>

#include "IUser.h"

using asyncFunction = std::function<void(std::shared_ptr<ClientSocket>, std::string&, std::function<void(int)>)>;


class User: public IUser, public std::enable_shared_from_this<User> {
private:
    std::string buffer;
    int sessionId;

    asyncFunction mAsyncRead;
    asyncFunction mAsyncWrite;

    std::function<int (const std::string&, std::shared_ptr<User>)> mSwitch;

    void readHandler(int error);
    void writeHandler(int error);
public:
    User(std::shared_ptr<ClientSocket> sock, const asyncFunction& asyncRead, const asyncFunction& asyncWrite, std::function<int (const std::string&, std::shared_ptr<User>)> switchF):
            IUser(sock), mAsyncRead(asyncRead), mAsyncWrite(asyncWrite), mSwitch(switchF){}
    void write(const std::string& message) override;
    void read() override;

    void setSessionId(int session) {
        sessionId = session;
    }
};

using UserPtr = std::shared_ptr<User>;


#endif //PROJECT_SERVER_USER_H
