#ifndef SEABATTLE_NETWORK_INTERFACE_H
#define SEABATTLE_NETWORK_INTERFACE_H

#include <cstddef>
#include <string>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

namespace seabattle {
namespace client {
namespace network {

class INetworkClient {
 public:
    virtual ~INetworkClient() = default;
    virtual void Run(std::shared_ptr<std::stringstream> data,
                     std::shared_ptr<std::function<size_t(std::stringstream&)>> callback,
                     int debug_param) = 0;
    virtual void Close() = 0;

 private:
    virtual void OnConnect(const boost::system::error_code& ErrorCode) = 0;
    virtual void OnReceive(const boost::system::error_code& ErrorCode,
                           std::shared_ptr<std::function<size_t(std::stringstream&)>> callback,
                           size_t bytes_transferred, int debug_param) = 0;
    virtual void OnSend(const boost::system::error_code& ErrorCode,
                        std::shared_ptr<std::function<size_t(std::stringstream&)>> callback,
                        int debug_param) = 0;
    virtual void DoClose() = 0;
};

}  // namespace network
}  // namespace client
}  // namespace seabattle

#endif  // SEABATTLE_NETWORK_INTERFACE_H