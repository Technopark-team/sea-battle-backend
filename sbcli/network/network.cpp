#include "network.h"

namespace seabattle {
namespace client {
namespace network {

TCPClient::TCPClient(config::IpPort ip_port) : send_buffer_(""), ip_port_(std::move(ip_port)) {
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(ip_port_.ip),
                                            ip_port_.port);
    io_service_ = std::make_shared<boost::asio::io_service>();
    socket_ = std::make_shared<tcp::socket>(*io_service_);
    socket_->async_connect(
        endpoint, boost::bind(&TCPClient::OnConnect, this, boost::asio::placeholders::error));
    io_service_->run();
}

/*
 * TODO: проверять перед отправкой отсуствие нулей, которые могут превратиться в терминирующие или
 * решить проблему их появления
 */

/*
 * TODO: решить проблему передачи коллбека по цепочке асинхронных вызовов, а, может, лучше добавить
 * к коллбеку доп параметр, чтобы на любом этапе работы с сетью была возможность сообщить
 * модели о проблеме и как следствие пользователю об ошибке
 */

void TCPClient::Run(std::shared_ptr<std::stringstream> data,
                    std::shared_ptr<std::function<size_t(std::stringstream&)>> callback,
                    int debug_param) {
    std::cout << "[NETWORK] Client is starting..." << std::endl;
    send_buffer_ = data->str();
    callback_ = callback;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(ip_port_.ip),
                                            ip_port_.port);
    send_buffer_ += "\0";

    socket_->async_send(boost::asio::buffer(send_buffer_.c_str(), send_buffer_.length() + 1),
                        boost::bind(&TCPClient::OnSend, this, boost::asio::placeholders::error,
                                    callback, debug_param));
    std::cout << "[NETWORK] Client is started!" << std::endl;

    io_service_->reset();
    io_service_->run();
}

void TCPClient::Close() { io_service_->post(boost::bind(&TCPClient::DoClose, this)); }

void TCPClient::OnConnect(const boost::system::error_code& ErrorCode) {
    std::cout << "[NETWORK] OnConnect..." << std::endl;
    if (ErrorCode.value() == boost::system::errc::success) {
        std::cout << "[NETWORK] Entered and serialized: " << send_buffer_ << endl;
        send_buffer_ += "\0";
    } else {
        throw std::logic_error("[NETWORK] Can not connect to server");
    }
}

void TCPClient::OnReceive(const boost::system::error_code& ErrorCode,
                          std::shared_ptr<std::function<size_t(std::stringstream&)>> callback,
                          size_t bytes_transferred, int debug_param) {
    std::cout << "[NETWORK] receiving... " << bytes_transferred << " bytes" << std::endl;
    if (ErrorCode.value() == boost::system::errc::success) {
        std::cout << "[NETWORK] Serialized data received \"" << receive_buffer_ << "\""
                  << std::endl;
        std::stringstream ss{};
        ss << receive_buffer_;
        callback_->operator()(ss);
        if (debug_param == 2) {
            std::cout << "[NETWORK] Additional receive" << std::endl;

            socket_->async_read_some(
                boost::asio::buffer(receive_buffer_, buf_len_),
                boost::bind(&TCPClient::OnReceive, this, boost::asio::placeholders::error, callback,
                            boost::asio::placeholders::bytes_transferred, debug_param));
        }
        //        DoClose();
    } else {
        std::cerr << "[NETWORK] ERROR! OnReceive... with error = " << ErrorCode.value()
                  << std::endl;
        std::cerr << ErrorCode.message() << std::endl;
        DoClose();
    }
}

void TCPClient::OnSend(const boost::system::error_code& ErrorCode,
                       std::shared_ptr<std::function<size_t(std::stringstream&)>> callback,
                       int debug_param) {
    std::cout << "[NETWORK] sending..." << std::endl;
    if (!ErrorCode) {
        std::cout << "[NETWORK] \"" << send_buffer_ << "\" has been sent" << std::endl;
        send_buffer_ = "";
        socket_->async_receive(
            boost::asio::buffer(receive_buffer_, buf_len_),
            boost::bind(&TCPClient::OnReceive, this, boost::asio::placeholders::error, callback,
                        boost::asio::placeholders::bytes_transferred, debug_param));
    } else {
        std::cout << "[NETWORK] OnSend closing" << std::endl;
        DoClose();
    }
}

void TCPClient::DoClose() { socket_->close(); }

}  // namespace network
}  // namespace client
}  // namespace seabattle