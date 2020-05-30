#include "include/DBAccess.h"

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
