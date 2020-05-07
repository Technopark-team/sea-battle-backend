#include "network.h"

namespace seabattle {
namespace client {
namespace network {

NetworkClient::NetworkClient() {}
size_t NetworkClient::Fail(std::string error) { return 0; }
size_t NetworkClient::OnRead(std::string error) { return 0; }
size_t NetworkClient::OnWrite(std::string error) { return 0; }
size_t NetworkClient::OnConnect(std::string error) { return 0; }
size_t NetworkClient::OnResolve(std::string error) { return 0; }

}
}
}