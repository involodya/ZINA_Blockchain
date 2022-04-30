// #include "definitions.h"
#include "Miner.h"
//#include "Transaction.h"
#include "BlockChain.h"
//#include "Block.cpp"
//#include "Hash.h"
#include "User.h"
//#include "ZINA.h"
#include "CPKey.h"
//#include "Miner.h"
//#include "hash_functions.cpp"
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
//    ecdsa();
/*
    for (int i = 0; i < 10; ++i) {
        std::cerr << i << std::endl;
        User u;
        u.dbg();
        std::cerr << i << std::endl;
    }
    std::cerr << 322 << std::endl;
*/

    User u1;
    User u2;
    u1.dbg();
    u2.dbg();
    Transaction t(u1.getCPKey(), u2.getCPKey(), ZINA(10), "HW!");
    t.dbg();
    u1.signTransaction(t);
    t.dbg();
    Miner m;
    std::cerr << m.verify_transaction(t) << std::endl;
    std::cerr << t.getValueHash() << std::endl;
    Block b;
    b.addTransaction(t);
    Block b_mined = m.mine(b);
//    b_mined.dbg();

/*
    secp256k1_context *ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY);
    uint8_t randomize[32];
    fill_random(randomize, sizeof(randomize));
    auto return_val = secp256k1_context_randomize(ctx, randomize);
    assert(return_val);

    //Key Generation

    uint8_t seckey[SECRET_KEY_SIZE];
    while (true) {
        fill_random(seckey, sizeof(seckey));
        if (secp256k1_ec_seckey_verify(ctx, seckey)) {
            break;
        }
    }

    secp256k1_pubkey pubkey;
    return_val = secp256k1_ec_pubkey_create(ctx, &pubkey, seckey);

    auto compressed_pubkey = new uint8_t[COMPRESSED_PUBLIC_KEY_SIZE];
    size_t len = COMPRESSED_PUBLIC_KEY_SIZE;
    return_val = secp256k1_ec_pubkey_serialize(ctx, compressed_pubkey, &len, &pubkey, SECP256K1_EC_COMPRESSED);

    std::cerr << "Origin public Key:\t";
    print_hex(compressed_pubkey, COMPRESSED_PUBLIC_KEY_SIZE);


    secp256k1_pubkey pubkey2;
    secp256k1_ec_pubkey_parse(ctx, &pubkey2, compressed_pubkey, COMPRESSED_PUBLIC_KEY_SIZE);

    auto compressed_pubkey2 = new uint8_t[COMPRESSED_PUBLIC_KEY_SIZE];
    size_t len2 = COMPRESSED_PUBLIC_KEY_SIZE;
    return_val = secp256k1_ec_pubkey_serialize(ctx, compressed_pubkey2, &len2, &pubkey2, SECP256K1_EC_COMPRESSED);

    std::cerr << "Parsed public Key:\t";
    print_hex(compressed_pubkey2, COMPRESSED_PUBLIC_KEY_SIZE);
    secp256k1_context_destroy(ctx);
*/
/*
    secp256k1_context *ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY);
    uint8_t randomize[32];
    fill_random(randomize, sizeof(randomize));
    auto return_val = secp256k1_context_randomize(ctx, randomize);
    assert(return_val);

    //Key Generation

    uint8_t seckey[SECRET_KEY_SIZE];
    while (true) {
        fill_random(seckey, sizeof(seckey));
        if (secp256k1_ec_seckey_verify(ctx, seckey)) {
            break;
        }
    }

    secp256k1_pubkey pubkey;
    return_val = secp256k1_ec_pubkey_create(ctx, &pubkey, seckey);

    CPKey ckey(pubkey);
    ckey.dbg();

    secp256k1_context_destroy(ctx);
*/
}
