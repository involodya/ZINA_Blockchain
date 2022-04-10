// #include "definitions.h"
//#include "Miner.h"
#include "Transaction.h"
//#include "Block.cpp"
#include "Hash.h"
#include "User.h"
#include "ZINA.h"
#include "hash_functions.cpp"
//#include <boost/asio.hpp>

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
/*
    freopen("output.txt", "w+", stdout);

    Transaction t1(sha256("1"), sha256("2"), ZINA(100));
    Transaction t2(sha256("2"), sha256("1"), ZINA(100));
    Block b1;
    b1.addTransaction(t1);
    b1.addTransaction(t2);
    for (int i = 0; i < 1e2; ++i) {
        auto time = clock();
        Transaction t(sha256("2"), sha256("1"), ZINA(i));
        b1.addTransaction(t1);
        std::cout << i << ": " << calculateHash(b1) << ' ' << (clock() - time) * 1000.0 / CLOCKS_PER_SEC << std::endl;
    }
    std::cerr << calculateHash(b1) << ' ' << clock() * 1000.0 / CLOCKS_PER_SEC << std::endl;
    clock();


*/
/*
    Hash h1("Hello, world!");
    Hash h2;
    h1.dbg();
    h2.dbg();

    h2 = h1;
    h1.dbg();
    h2.dbg();
    */
    ecdsa();
/*
    for (int i = 0; i < 10; ++i) {
        std::cerr << i << std::endl;
        User u;
        u.dbg();
        std::cerr << i << std::endl;
    }
    std::cerr << 322 << std::endl;*/
    User u1;
    User u2;
    u1.dbg();
    u2.dbg();
    Transaction t(u1.getHash(), u2.getHash(), ZINA(10));
    t.dbg();
    u1.signTransaction(t);
    t.dbg();
}
