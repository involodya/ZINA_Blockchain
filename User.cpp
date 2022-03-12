#include "User.h"

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
