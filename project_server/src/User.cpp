#include "User.h"
#include <iostream>

void User::write(const std::string &message) {
    buffer = message;
    auto cb = [usr = shared_from_this()](int error){
        usr->writeHandler(error);
    };
    mAsyncWrite(m_socket, std::ref(buffer), cb);
}

void User::read() {
    auto cb = [usr = shared_from_this()](int error){
        usr->readHandler(error);
    };
    mAsyncRead(m_socket, std::ref(buffer), cb);
}

void User::writeHandler(int error) {
    read();
}

void User::readHandler(int error) {
    auto usr = shared_from_this();
    int res = mSwitch(buffer, usr);


}
