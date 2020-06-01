#include "network.h"

namespace seabattle {
namespace client {
namespace network {

TCPClient::TCPClient(boost::asio::io_service& IO_Service, config::IpPort ip_port)
    : io_service_(IO_Service),
      socket_(IO_Service),
      send_buffer_(""),
      ip_port_(std::move(ip_port)) {}

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
                    std::shared_ptr<std::function<size_t(std::stringstream&)>> callback) {
    send_buffer_ = data->str();
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(ip_port_.ip),
                                            ip_port_.port);
    boost::asio::io_service ioc;
    socket_ = tcp::socket(ioc);
    socket_.async_connect(endpoint, boost::bind(&TCPClient::OnConnect, this,
                                                boost::asio::placeholders::error, callback));
    ioc.run();
}

void TCPClient::Close() { io_service_.post(boost::bind(&TCPClient::DoClose, this)); }
void TCPClient::OnConnect(const boost::system::error_code& ErrorCode,
                          std::shared_ptr<std::function<size_t(std::stringstream&)>> callback) {
    cout << "OnConnect..." << endl;
    if (ErrorCode.value() == boost::system::errc::success) {
        //        std::cout << "Enter a query string " << std::endl;
        //        cin >> send_buffer_;
        cout << "Entered: " << send_buffer_ << endl;
        send_buffer_ += "\0";

        socket_.async_send(
            boost::asio::buffer(send_buffer_.c_str(), send_buffer_.length() + 1),
            boost::bind(&TCPClient::OnSend, this, boost::asio::placeholders::error, callback));
    }
}

void TCPClient::OnReceive(const boost::system::error_code& ErrorCode,
                          std::shared_ptr<std::function<size_t(std::stringstream&)>> callback) {
    cout << "receiving..." << endl;
    if (ErrorCode.value() == boost::system::errc::success) {
        cout << receive_buffer_ << endl;
        std::stringstream ss{};
        ss << receive_buffer_;
        callback->operator()(ss);
        DoClose();

        //        socket_.async_receive(boost::asio::buffer(recieve_buffer_, buf_len_),
        //                               boost::bind(&TCPClient::OnReceive, this,
        //                               boost::asio::placeholders::error));
    } else {
        cout << "ERROR! OnReceive..." << endl;
        DoClose();
    }
}

void TCPClient::OnSend(const boost::system::error_code& ErrorCode,
                       std::shared_ptr<std::function<size_t(std::stringstream&)>> callback) {
    cout << "sending..." << endl;
    if (!ErrorCode) {
        cout << "\"" << send_buffer_ << "\" has been sent" << endl;
        send_buffer_ = "";

        socket_.async_receive(
            boost::asio::buffer(receive_buffer_, buf_len_),
            boost::bind(&TCPClient::OnReceive, this, boost::asio::placeholders::error, callback));
    } else {
        cout << "OnSend closing" << endl;
        DoClose();
    }
}

void TCPClient::DoClose() { socket_.close(); }

}  // namespace network
}  // namespace client
}  // namespace seabattle