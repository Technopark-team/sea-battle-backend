#ifndef SEA_BATTLE_BACKEND_NETWORK_H
#define SEA_BATTLE_BACKEND_NETWORK_H

#include "network_interface.h"

namespace seabattle {
namespace client {
namespace network {

class NetworkClient : public INetworkClient {
 public:
    explicit NetworkClient();
    ~NetworkClient() = default;

    size_t Fail(std::string error) override;
    size_t OnRead(std::string error) override;
    size_t OnWrite(std::string error) override;
    size_t OnConnect(std::string error) override;
    size_t OnResolve(std::string error) override;

};

}  // namespace network
}  // namespace client
}  // namespace seabattle

#endif //SEA_BATTLE_BACKEND_NETWORK_H
