#pragma once
#include <list>
#include "Transaction.h"

struct Block {
public:
    void setNonce(nonce_t new_nonce);
    nonce_t _nonce = 0;
    std::list<Transaction> _listOfTransactions;
    hash_t _previousBlockHash;
    hash_t _currentBlockHash;
};