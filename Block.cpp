#include "Block.h"

Block::Block() : _nonce(0), _previousBlockHash(DEFAULT_HASH), _currentBlockHash(DEFAULT_HASH), _listOfTransactions({}) {}

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

void Block::addTransaction(const Transaction &transaction) {
    _listOfTransactions.emplace_back(transaction);
}
