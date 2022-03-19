#include "Block.h"

void Block::setNonce(nonce_t new_nonce) {
    _nonce = new_nonce;
}

Block::Block() {
    nonce_t _nonce = 0;
    std::list<Transaction> _listOfTransactions;
    hash_t _previousBlockHash = DEFAULT_HASH;
    hash_t _currentBlockHash = DEFAULT_HASH;
}
/*
 Block();
    void setNonce(nonce_t new_nonce);
    nonce_t _nonce = 0;
    std::list<Transaction> _listOfTransactions;
    hash_t _previousBlockHash;
    hash_t _currentBlockHash;
};
*/