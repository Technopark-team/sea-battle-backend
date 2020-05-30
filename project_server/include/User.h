#ifndef PROJECT_SERVER_USER_H
#define PROJECT_SERVER_USER_H

#include <string>
#include <memory>
#include <functional>

#include "IUser.h"

using AsyncFunction = std::function<void(std::shared_ptr<ClientSocket>, std::string&, std::function<void(int)>)>;


class User: public IUser, public std::enable_shared_from_this<User> {
private:
    std::string buffer_;
    size_t session_id_;

    AsyncFunction m_async_read_;
    AsyncFunction m_async_write_;

    std::function<int (const std::string&, std::shared_ptr<User>)> m_switch_;

    void ReadHandler(int error);
    void WriteHandler(int error);
public:
    User(std::shared_ptr<ClientSocket> sock): IUser(sock) {}
    User(std::shared_ptr<ClientSocket> sock, const AsyncFunction& async_read, const AsyncFunction& async_write, std::function<int (const std::string&, std::shared_ptr<User>)> switch_f):
            IUser(sock), m_async_read_(async_read), m_async_write_(async_write), m_switch_(switch_f){}
    void write(const std::string& message) override;
    void read() override;

    void SetSessionId(size_t session);
    size_t GetSessionId();

    ~User() = default;
};

using UserPtr = std::shared_ptr<User>;


#endif //PROJECT_SERVER_USER_H
