#ifndef PROJECT_SERVER_DBACCESS_H
#define PROJECT_SERVER_DBACCESS_H
#include <sw/redis++/redis++.h>
#include <iostream>

class DBAccess {
public:
    DBAccess(): redis(sw::redis::Redis("tcp://127.0.0.1:6379")) {
    }
    ~DBAccess() = default;

    bool AddUser(const std::string& login, const std::string& password);
    bool CheckUser(const std::string& login, const std::string& password);
private:
    sw::redis::Redis redis;
};

bool DBAccess::AddUser(const std::string& login, const std::string& password) {
  if (redis.get(login)) {
    return false;
  }
  return redis.set(login, password);
}

bool DBAccess::CheckUser(const std::string& login, const std::string& password) {
  if (!redis.get(login)) {
    return false;
  }
  return password == redis.get(login).value();
}

#endif //PROJECT_SERVER_DBACCESS_H
