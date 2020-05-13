#ifndef SEA_BATTLE_BACKEND_NETWORK_H
#define SEA_BATTLE_BACKEND_NETWORK_H

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
    TCPClient(boost::asio::io_service& IO_Service);
    ~TCPClient() = default;

    void Run(std::shared_ptr<std::stringstream> data,
             std::shared_ptr<std::function<size_t(std::stringstream&)>> callback) override;
    void Close() override;

 private:
    boost::asio::io_service& io_service_;
    tcp::socket socket_;

    string send_buffer_;
    static const size_t buf_len_ = 5000;
    char recieve_buffer_[buf_len_ * 2];

    void OnConnect(const boost::system::error_code& ErrorCode,
                   std::shared_ptr<std::function<size_t(std::stringstream&)>> callback) override;
    void OnReceive(const boost::system::error_code& ErrorCode,
                   std::shared_ptr<std::function<size_t(std::stringstream&)>> callback) override;
    void OnSend(const boost::system::error_code& ErrorCode,
                std::shared_ptr<std::function<size_t(std::stringstream&)>> callback) override;
    void DoClose() override;
};

}  // namespace network
}  // namespace client
}  // namespace seabattle

#endif  // SEA_BATTLE_BACKEND_NETWORK_H
