#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/smart_ptr.hpp>

using boost::asio::ip::tcp;
typedef boost::shared_ptr<tcp::socket> socket_ptr;

void session(socket_ptr sock) {
    try {
        while(true) {
            char data[10023];
            boost::system::error_code ec;
            size_t length = sock->read_some(boost::asio::buffer(data), ec);
            if (ec == boost::asio::error::eof) {
                break;
            } else if (ec) {
                throw boost::system::system_error(ec);
            }
            boost::asio::write(*sock, boost::asio::buffer(data, length));
        }
    } catch (std::exception &e) {
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }
}

void server(boost::asio::io_service &io_service, int port) {
    tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
    while (true) {
        socket_ptr sock(new tcp::socket(io_service));
        a.accept(*sock);
        boost::thread t(boost::bind(session, sock));
    }
}
int main (int argc, char* argv[]) {
    try {
        if (argc != 2) {
            std::cout << "Usage: blocking_tcp_echo_server <port>\n";
            return -1;
        }
        boost::asio::io_service io_service;
        server(io_service, atoi(argv[1]));
    } catch (std::exception &e) {
        std::cerr << "Exception:" << e.what() << "\n";
    }

}
