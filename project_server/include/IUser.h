#ifndef PROJECT_SERVER_IUSER_H
#define PROJECT_SERVER_IUSER_H
#include <string>

#include "ClientSocket.h"

class IUser {
private:
    static size_t next_id;
protected:
    std::shared_ptr<ClientSocket> m_socket;
    std::string name;
    size_t id;
public:
    explicit IUser(std::shared_ptr<ClientSocket> sock);
    virtual ~IUser() = default;

    void set_name(const std::string& username);
    virtual void write(const std::string& message) = 0;
    virtual void read() = 0;
    size_t get_id();
    std::shared_ptr<ClientSocket> get_client();
};


#endif //PROJECT_SERVER_IUSER_H
