#include <iostream>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

/*
Test version
*/

using boost::asio::ip::tcp;

typedef boost::shared_ptr<tcp::socket> socket_ptr;

void session(const socket_ptr& sock);

void client() {
    try {
        boost::asio::io_service io_service;
        tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 1234);
        std::cout << ep.address() << std::endl;

        tcp::socket socket(io_service);
        socket.connect(ep);
        if (socket.is_open()) {
            std::cout << "connect!" << std::endl;
        }
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}


int main() {
    boost::thread cl(&client);
    boost::asio::io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1234));
    socket_ptr sock(new tcp::socket(io_service));
    acceptor.accept(*sock);
    boost::thread t([sock] { return session(sock); });
    cl.join();
    t.join();
}


void session(const socket_ptr& sock) {
    std::cout << "connect!" << std::endl;
}