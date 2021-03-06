#include <iostream>
#include <memory>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public :
    Session(boost::asio::io_service &io_service) :
        _socket(io_service) {
    }
    tcp::socket &socket() {
        return _socket;
    }
    void start() {
        handle_read();
    }
private:
    void handle_read() {
        auto self(shared_from_this());
        _socket.async_read_some(boost::asio::buffer(_data),
            [this, self](boost::system::error_code ec, size_t length){
                if (!ec) {
                    handle_write(length);
                }
            }
        );
    }
    void handle_write(size_t length) {
        auto self(shared_from_this());
        boost::asio::async_write(_socket, boost::asio::buffer(_data, length), 
            [this, self] (boost::system::error_code ec, size_t) {
                if (!ec) {
                    handle_read();
                }
            }
        );
    }
private:
    tcp::socket _socket;
    char _data[10086];
};

class Server {
public :
    Server(boost::asio::io_service &io_service, int port) : 
        _io_service(io_service), _acceptor(io_service, tcp::endpoint(tcp::v4(), port))
    {
        start_accept();
    }
private:
    void start_accept() {
        Session *session = new Session(_io_service);
        _acceptor.async_accept(session->socket(), 
            boost::bind(&Server::handle_accept, this, session, boost::asio::placeholders::error));
    }
    void handle_accept(Session *session, const boost::system::error_code& error) {
        if (!error) {
            session->start();
        } else {
            delete session;
        }
        start_accept();
    }
private:
    tcp::acceptor _acceptor;
    boost::asio::io_service &_io_service;
};


int main (int argc, char *argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Usage : async_tcp_echo_server <port>\n" ;
            return 1;
        }
        boost::asio::io_service io_service;
        Server *server = new Server(io_service, std::atoi(argv[1]));
        io_service.run();
    } catch (std::exception &e) {
        std::cerr << "Exception : " << e.what() <<"\n";
    }
}

