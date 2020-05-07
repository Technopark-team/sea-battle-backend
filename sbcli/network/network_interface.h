#ifndef SEABATTLE_NETWORK_INTERFACE_H
#define SEABATTLE_NETWORK_INTERFACE_H

#include <cstddef>
#include <string>

namespace seabattle {
namespace client {
namespace network {

class INetworkClient {
 public:
    virtual ~INetworkClient() = default;

    virtual size_t Fail(std::string error) = 0;
    virtual size_t OnRead(std::string error) = 0;
    virtual size_t OnWrite(std::string error) = 0;
    virtual size_t OnConnect(std::string error) = 0;
    virtual size_t OnResolve(std::string error) = 0;

};

}  // namespace network
}  // namespace client
}  // namespace seabattle

#endif  // SEABATTLE_NETWORK_INTERFACE_H
