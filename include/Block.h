#pragma once

#include <list>
#include "Transaction.h"
#include "Coinbase.h"

struct Block {
    Block();

    nonce_t _nonce;

    hash_t _previousBlockHash;
    hash_t _currentBlockHash;

    std::list<Transaction> _listOfTransactions;
    Coinbase coinbase_transaction;
    void setNonce(nonce_t new_nonce);
    void addTransaction(const Transaction& transaction);

    hash_t calculateHash() const;

    void dbg() const;
};
