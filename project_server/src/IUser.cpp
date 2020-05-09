#include "IUser.h"
size_t IUser::next_id = 1;

IUser::IUser(std::shared_ptr<ClientSocket> sock): m_socket(sock), id(next_id++){

}

size_t IUser::get_id() {
    return id;
}

void IUser::set_name(const std::string& username) {
    name = username;
}

std::shared_ptr<ClientSocket> IUser::get_client() {
    return std::shared_ptr<ClientSocket>();
}

