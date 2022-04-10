#include "User.h"

void User::dbg() const {
    std::cerr << "User" << std::endl;
    std::cerr << "_user_hash = " << _user_hash << std::endl;
    std::cerr << "_public_key = " << _public_key << std::endl;
    std::cerr << "_private_key = " << _private_key << std::endl;
    std::cerr << std::endl;
}

User::User() {
    rsa_pair_t _keys = generateKeys();
    _public_key = _keys.first;
    _private_key = _keys.second;
}

User::User(rsa_pair_t _keys) : _public_key(_keys.first), _private_key(_keys.second) {}

void User::sendTransaction(Transaction &transaction) {
    signTransaction(transaction);

    //TODO send to network
}

//TODO realization
void User::signTransaction(Transaction &transaction) {
    transaction._signature = "";
}
