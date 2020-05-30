#include "User.h"
#include <iostream>

void User::write(const std::string& message) {
    buffer_ = message;
    auto cb = [usr = shared_from_this()](int error) {
        usr->WriteHandler(error);
    };
    m_async_write_(socket_, std::ref(buffer_), cb);
}

void User::read() {
    auto cb = [usr = shared_from_this()](int error){
        usr->ReadHandler(error);
    };
    m_async_read_(socket_, std::ref(buffer_), cb);
}

void User::WriteHandler(int error) {
    read();
}

void User::ReadHandler(int error) {
    auto usr = shared_from_this();
    m_switch_(buffer_, usr);
}

void User::SetSessionId(size_t session) {
    session_id_ = session;
}

size_t User::GetSessionId() {
    return session_id_;
}