#ifndef SEA_BATTLE_BACKEND_NETWORK_H
#define SEA_BATTLE_BACKEND_NETWORK_H

#include <sbcli/config/config.h>
#include "network_interface.h"

#include <iostream>
#include <string>

namespace seabattle {
namespace client {
namespace network {

// TODO: добавить документацию к методам и свойствам

using namespace std;

using boost::asio::ip::tcp;

class TCPClient : public INetworkClient {
 public:
    TCPClient(config::IpPort ip_port);
    ~TCPClient() = default;

    void Run(std::shared_ptr<std::stringstream> data,
             std::shared_ptr<std::function<size_t(std::stringstream&)>> callback,
             int debug_param) override;
    void Close() override;

 private:
    std::shared_ptr<boost::asio::io_service> io_service_;
    std::shared_ptr<tcp::socket> socket_;

    string send_buffer_;
    static const size_t buf_len_ = 20000;
    char receive_buffer_[buf_len_ * 2];

    std::shared_ptr<std::function<size_t(std::stringstream&)>> callback_;

    config::IpPort ip_port_;

    void OnConnect(const boost::system::error_code& ErrorCode) override;
    void OnReceive(const boost::system::error_code& ErrorCode,
                   std::shared_ptr<std::function<size_t(std::stringstream&)>> callback,
                   size_t bytes_transferred, int debug_param) override;
    void OnSend(const boost::system::error_code& ErrorCode,
                std::shared_ptr<std::function<size_t(std::stringstream&)>> callback,
                int debug_param) override;
    void DoClose() override;
};

}  // namespace network
}  // namespace client
}  // namespace seabattle

#endif  // SEA_BATTLE_BACKEND_NETWORK_H