#pragma once
#include <list>
#include "Transaction.h"

struct Block {
    Block();

    nonce_t _nonce;

    hash_t _previousBlockHash;
    hash_t _currentBlockHash;

    std::list<Transaction> _listOfTransactions;

    void setNonce(nonce_t new_nonce);
    void addTransaction(const Transaction& transaction);

    void dbg() const;
};
