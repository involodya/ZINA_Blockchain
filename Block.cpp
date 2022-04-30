#include "Block.h"

Block::Block() : _nonce(0), _listOfTransactions({}) {}

template<class Archive>
void Block::serialize(Archive &ar, const unsigned version) {
    ar & _nonce;
    ar & _previousBlockHash;
    ar & _currentBlockHash;
    ar & _listOfTransactions;
    ar & coinbase_transaction;
}

void Block::setNonce(nonce_t new_nonce) {
    _nonce = new_nonce;
}

void Block::dbg() const {
    std::cerr << "_nonce: " << _nonce << std::endl;
    std::cerr << "_previousBlockHash: " << _previousBlockHash << std::endl;
    std::cerr << "_currentBlockHash: " << _currentBlockHash << std::endl;
    std::cerr << "_listOfTransactions: \n";
    for (const Transaction &transaction: _listOfTransactions) {
        std::cerr << "    {" << transaction << '}' << '\n';
    }
    std::cerr << std::endl;
}

std::ostream& operator<<(std::ostream& out, const Block& block) {
    out << block._nonce << std::endl;
    out << block._previousBlockHash << std::endl;
    out << block._currentBlockHash << std::endl;
    for (const Transaction &transaction: block._listOfTransactions) {
        out << transaction << '\n';
    }
    out << std::endl;
    return out;
}


void Block::addTransaction(const Transaction &transaction) {
    _listOfTransactions.emplace_back(transaction);
}

hash_t Block::calculateHash() const {
    std::stringstream ss;
    ss << _nonce << _previousBlockHash << _currentBlockHash;
    for (const Transaction &transaction: _listOfTransactions) {
        ss << '{' << transaction << '}';
    }
    return Hash(ss.str());
}
