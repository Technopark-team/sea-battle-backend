#include "IUser.h"
size_t IUser::next_id = 1;

IUser::IUser(std::string username, int sock): name(std::move(username)), m_socket(sock), id(next_id++){

}

size_t IUser::get_id() {
    return 0;
}
