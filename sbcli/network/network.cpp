#include "network.h"

namespace seabattle {
namespace client {
namespace network {

TCPClient::TCPClient(boost::asio::io_service& IO_Service)
    : io_service_(IO_Service), socket_(IO_Service), send_buffer_("") {}

void TCPClient::Run(std::shared_ptr<std::stringstream> data,
                    std::shared_ptr<std::function<size_t(std::stringstream&)>> callback) {
    send_buffer_ = data->str();
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"),
                                            8089);
    socket_.async_connect(
        endpoint, boost::bind(&TCPClient::OnConnect, this, boost::asio::placeholders::error, callback));
    io_service_.run();
}

void TCPClient::Close() { io_service_.post(boost::bind(&TCPClient::DoClose, this)); }
void TCPClient::OnConnect(const boost::system::error_code& ErrorCode, std::shared_ptr<std::function<size_t(std::stringstream&)>> callback) {
    cout << "OnConnect..." << endl;
    if (ErrorCode.value() == boost::system::errc::success) {
        //        std::cout << "Enter a query string " << std::endl;
        //        cin >> send_buffer_;
        cout << "Entered: " << send_buffer_ << endl;
        send_buffer_ += "\0";

        socket_.async_send(boost::asio::buffer(send_buffer_.c_str(), send_buffer_.length() + 1),
                           boost::bind(&TCPClient::OnSend, this, boost::asio::placeholders::error, callback));
    }
}

void TCPClient::OnReceive(const boost::system::error_code& ErrorCode, std::shared_ptr<std::function<size_t(std::stringstream&)>> callback) {
    cout << "receiving..." << endl;
    if (ErrorCode.value() == boost::system::errc::success) {
        cout << recieve_buffer_ << endl;
        std::stringstream ss{};
        ss << recieve_buffer_;
        callback->operator()(ss);

        //        socket_.async_receive(boost::asio::buffer(recieve_buffer_, buf_len_),
        //                               boost::bind(&TCPClient::OnReceive, this,
        //                               boost::asio::placeholders::error));
    } else {
        cout << "ERROR! OnReceive..." << endl;
        DoClose();
    }
}

void TCPClient::OnSend(const boost::system::error_code& ErrorCode, std::shared_ptr<std::function<size_t(std::stringstream&)>> callback) {
    cout << "sending..." << endl;
    if (!ErrorCode) {
        cout << "\"" << send_buffer_ << "\" has been sent" << endl;
        send_buffer_ = "";

        socket_.async_receive(
            boost::asio::buffer(recieve_buffer_, buf_len_),
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