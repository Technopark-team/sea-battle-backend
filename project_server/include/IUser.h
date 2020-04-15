#ifndef PROJECT_SERVER_IUSER_H
#define PROJECT_SERVER_IUSER_H
#include <string>

class IUser {
private:
    static size_t next_id;
protected:
    int m_socket;
    std::string name;
    size_t id;
public:
    IUser(std::string username, int sock);
    virtual int send_message(std::string message) = 0;
    virtual int recieve_message(std::string message) = 0;
    size_t get_id();
};


#endif //PROJECT_SERVER_IUSER_H
