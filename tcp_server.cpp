// importing libraries
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <iostream>
#include "sbutils/serialization/serializer.h"

using namespace boost::asio;
using ip::tcp;
using std::cout;
using std::endl;

namespace utils = seabattle::utils;

class con_handler : public boost::enable_shared_from_this<con_handler> {
 private:
    tcp::socket sock;
    std::string message{};
    enum { max_length = 10000 };
    char data[max_length];

 public:
    typedef boost::shared_ptr<con_handler> pointer;
    con_handler(boost::asio::io_service& io_service) : sock(io_service) {}
    // creating the pointer
    static pointer create(boost::asio::io_service& io_service) {
        return pointer(new con_handler(io_service));
    }
    // socket creation
    tcp::socket& socket() { return sock; }

    void start() {
        sock.async_read_some(boost::asio::buffer(data, max_length),
                             boost::bind(&con_handler::handle_read, shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));

//        sock.async_write_some(boost::asio::buffer(message, message.length() + 1),
//                              boost::bind(&con_handler::handle_write, shared_from_this(),
//                                          boost::asio::placeholders::error,
//                                          boost::asio::placeholders::bytes_transferred));
    }

    void handle_read(const boost::system::error_code& err, size_t bytes_transferred) {
        if (!err) {
            cout << "Received data = " << data << endl;
            std::shared_ptr<std::stringstream> ss = std::make_shared<std::stringstream>();
            *ss << data;
            std::shared_ptr<utils::data::DataRequest> req =
                utils::serializer::Serializer<utils::data::DataRequest>::Deserialize(
                    *ss, ss->str().size());
            std::cout << req->route << std::endl;

            switch (req->route) {
                case utils::data::Routes::GET_GAME_ALL:
                    break;
                case utils::data::Routes::GET_GAME_OPEN:
                    break;
                case utils::data::Routes::GET_GAME_STEP:
                    break;
                case utils::data::Routes::GET_GAME_STATE:
                    break;
                case utils::data::Routes::POST_SIGN_IN: {
                    std::cout << req->auth_data.login << std::endl;
                    std::shared_ptr<utils::data::DataResponse> resp =
                        std::make_shared<utils::data::DataResponse>();
                    utils::data::UserData user_data = utils::data::UserData(65);
                    resp->user_data = user_data;
                    resp->route = utils::data::Routes::POST_SIGN_IN;
                    std::shared_ptr<std::stringstream> s_resp =
                        utils::serializer::Serializer<utils::data::DataResponse>::Serialize(*resp);
                    message = std::move(s_resp->str());
                    message += "\0";
                    std::cout << message << std::endl;
                    break;
                }
                case utils::data::Routes::POST_SIGN_UP:
                    break;
                case utils::data::Routes::POST_GAME_START:
                    break;
                case utils::data::Routes::POST_GAME_STEP:
                    break;
                case utils::data::Routes::PUT_GAME_SAVE:
                    break;
                case utils::data::Routes::PUT_GAME_STOP:
                    break;
            }

            sock.async_write_some(boost::asio::buffer(message, message.length() + 1),
                                  boost::bind(&con_handler::handle_write, shared_from_this(),
                                              boost::asio::placeholders::error,
                                              boost::asio::placeholders::bytes_transferred));

        } else {
            std::cerr << "error here1: " << err.message() << std::endl;

            sock.close();
        }
    }
    void handle_write(const boost::system::error_code& err, size_t bytes_transferred) {
        if (!err) {
            cout << "Server sent Hello message! => " << bytes_transferred << endl;
        } else {
            std::cerr << "error here1: " << err.message() << endl;
            sock.close();
        }
    }
};

class Server {
 private:
    tcp::acceptor acceptor_;
    boost::asio::io_service& io_service_;

    void start_accept() {
        // socket
        con_handler::pointer connection = con_handler::create(io_service_);

        // asynchronous accept operation and wait for a new connection.
        acceptor_.async_accept(connection->socket(),
                               boost::bind(&Server::handle_accept, this, connection,
                                           boost::asio::placeholders::error));
    }

 public:
    // constructor for accepting connection from client
    Server(boost::asio::io_service& io_service)
        : acceptor_(io_service, tcp::endpoint(ip::address::from_string("127.0.0.1"), 8089)),
          io_service_(io_service) {
        start_accept();
    }
    void handle_accept(con_handler::pointer connection, const boost::system::error_code& err) {
        if (!err) {
            connection->start();
        }
        start_accept();
    }
};

int main(int argc, char* argv[]) {
    try {
        boost::asio::io_service io_service;
        Server server(io_service);
        io_service.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << endl;
    }
    return 0;
}