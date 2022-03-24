// #include "definitions.h"
//#include "Miner.h"
#include "Transaction.h"
#include "Block.cpp"
#include "hash_functions.cpp"
#include <boost/asio.hpp>
#include <pair>

int main() {
/*
    using namespace boost::asio;
    io_service service;
    ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 2001);
    ip::tcp::socket sock(service);
    try {
        sock.connect(ep);
    }
    catch (boost::system::system_error const &e) {
        std::cout << "Warning: could not connect : " << e.what() << std::endl;
    }
*/
    freopen("output.txt", "w+", stdout);

    Transaction t1(sha256("1"), sha256("2"), 100);
    Transaction t2(sha256("2"), sha256("1"), 100);
    Block b1;
    b1.addTransaction(t1);
    b1.addTransaction(t2);
    for (int i = 0; i < 1e4; ++i) {
        auto time = clock();
        Transaction t(sha256("2"), sha256("1"), i);
        b1.addTransaction(t1);
        std::cout << i << ": " << calculateHash(b1) << ' ' << (clock() - time) * 1000.0 / CLOCKS_PER_SEC << std::endl;
    }
    std::cerr << calculateHash(b1) << ' ' << clock() * 1000.0 / CLOCKS_PER_SEC << std::endl;
    clock();
}
